
attribute vec2 vertexPosition;
attribute vec4 vertexColor;
attribute vec2 vertexUV;

varying vec2 fragmentPosition;
varying vec4 fragmentColor;
varying vec2 fragmentUV;

uniform mat4 camera;

void main()
{
  gl_Position.xy = (camera * vec4(vertexPosition, 0.0, 1.0)).xy;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;

  fragmentPosition = vertexPosition;

  fragmentColor = vertexColor;

  fragmentUV = vec2(vertexUV.x, vertexUV.y);
}
