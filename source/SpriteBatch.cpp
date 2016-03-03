#include "SpriteBatch.h"

#include <algorithm>

SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0)
{
}


SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Init()
{
    CreateVertexArray();
}

void SpriteBatch::Begin(SortType sortType /* = SortType::SORT_BY_TEXTURE*/)
{
    m_sortType = sortType;
    
    // Delete all glyphs and clear vector of pointers
    for (const Glyph* i : m_glyphs)
        delete i;
    m_glyphs.clear();
    
    // Delete all render batches and clear vector of pointers
    for (const RenderBatch* i : m_renderBatches)
        delete i;
    m_renderBatches.clear();
}

void SpriteBatch::Draw(glm::vec4 & destRect, glm::vec4 & uvRect, GLuint textureId, float depth, const Color & color)
{
    Glyph* newGlyph = new Glyph;

    newGlyph->texture = textureId;
    newGlyph->depth = depth;

    newGlyph->topLeft.color = color;
    newGlyph->topLeft.SetPosition(destRect.x, destRect.y);
    newGlyph->topLeft.SetUV(uvRect.x, uvRect.y);

    newGlyph->topRight.color = color;
    newGlyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y);
    newGlyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

    newGlyph->botRight.color = color;
    newGlyph->botRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
    newGlyph->botRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

    newGlyph->botLeft.color = color;
    newGlyph->botLeft.SetPosition(destRect.x, destRect.y + destRect.w);
    newGlyph->botLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

    m_glyphs.push_back(newGlyph);
}

void SpriteBatch::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    for (size_t i = 0; i < m_renderBatches.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_renderBatches[i]->m_texture);
        glDrawArrays(GL_TRIANGLES, m_renderBatches[i]->m_offset, m_renderBatches[i]->m_numVerticies);
    }
    glBindVertexArray(0);
}

void SpriteBatch::End()
{
    SortGlyphs();
    CreateRenderBatches();
}

void SpriteBatch::CreateRenderBatches()
{
    // This will store all the vertices that we need to upload to graphic card
    std::vector <Vertex> vertices;

    // Resizing vertices vector since each glyph is made with 6 vertices
    vertices.resize(m_glyphs.size() * 6);

    // Check if there is anything to render
    if (m_glyphs.empty())
        return;

    int offset = 0; // Current offset
    int cv = 0; // Current vertex

    // Add first batch
    m_renderBatches.push_back(new RenderBatch(offset, 6, m_glyphs[0]->texture));
    vertices[cv++] = m_glyphs[0]->topLeft;
    vertices[cv++] = m_glyphs[0]->botLeft;
    vertices[cv++] = m_glyphs[0]->botRight;
    vertices[cv++] = m_glyphs[0]->botRight;
    vertices[cv++] = m_glyphs[0]->topRight;
    vertices[cv++] = m_glyphs[0]->topLeft;
    offset += 6;

    // Add all the rest of glyphs
    for (size_t cg = 1; cg < m_glyphs.size(); cg++)
    {
        if (m_glyphs[cg]->texture != m_glyphs[cg - 1]->texture)
        {
            // Make new batch
            m_renderBatches.push_back(new RenderBatch(offset, 6, m_glyphs[cg]->texture));
        }
        else
        {
            // If this is part of current batch just increase number of vertices
            m_renderBatches.back()->m_numVerticies += 6;
        }

        // Set vertices for current glyph
        vertices[cv++] = m_glyphs[cg]->topLeft;
        vertices[cv++] = m_glyphs[cg]->botLeft;
        vertices[cv++] = m_glyphs[cg]->botRight;
        vertices[cv++] = m_glyphs[cg]->botRight;
        vertices[cv++] = m_glyphs[cg]->topRight;
        vertices[cv++] = m_glyphs[cg]->topLeft;
        offset += 6;
    }

    // Bind our vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    // Upload data to buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    // Unbind the vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::SortGlyphs()
{
    switch (m_sortType)
    {
    case SortType::BACK_TO_FRONT:
        std::stable_sort(m_glyphs.begin(), m_glyphs.end(), BackToFront);
        break;
    case SortType::FRONT_TO_BACK:
        std::stable_sort(m_glyphs.begin(), m_glyphs.end(), FrontToBack);
        break;
    case SortType::SORT_BY_TEXTURE:
        std::stable_sort(m_glyphs.begin(), m_glyphs.end(), SortByTexture);
        break;
    }
}

void SpriteBatch::CreateVertexArray()
{
    // Create vertax buffer object
    if (m_vbo == 0)
        glGenBuffers(1, &m_vbo);
    // Bind vertax buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool SpriteBatch::FrontToBack(Glyph * a, Glyph * b)
{
    return (a->depth < b->depth);
}

bool SpriteBatch::BackToFront(Glyph * a, Glyph * b)
{
    return (a->depth > b->depth);
}

bool SpriteBatch::SortByTexture(Glyph * a, Glyph * b)
{
    return (a->texture < b->texture);
}

RenderBatch::RenderBatch(GLuint offset, GLuint numVerticies, GLuint texture)
    : m_offset(offset), m_numVerticies(numVerticies), m_texture(texture)
{
}