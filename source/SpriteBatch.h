#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "IwGL.h"
#include "Vertex.h"

enum class SortType {FRONT_TO_BACK, BACK_TO_FRONT, SORT_BY_TEXTURE};

struct Glyph
{
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex topRight;
    Vertex botLeft;
    Vertex botRight;
};

class RenderBatch
{
public:
    RenderBatch(GLuint offset, GLuint numVerticies, GLuint texture);
    GLuint m_offset;
    GLuint m_numVerticies;
    GLuint m_texture;
};

class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch();

    void Init();
    void Begin(SortType sortType = SortType::SORT_BY_TEXTURE);
    void Draw(glm::vec4& destRect, glm::vec4& uvRect,
        GLuint textureId, float depth, const Color& color);
    void Render();
    void End();

    
private:
    void SortGlyphs();
    void CreateVertexArray();
    void CreateRenderBatches();

    static bool FrontToBack(Glyph* a, Glyph* b);
    static bool BackToFront(Glyph* a, Glyph* b);
    static bool SortByTexture(Glyph* a, Glyph* b);

    std::vector <RenderBatch*>   m_renderBatches;
    std::vector <Glyph*>        m_glyphs;
    SortType                    m_sortType;

    GLuint m_vao;
    GLuint m_vbo;
};

