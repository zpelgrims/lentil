#version 450

layout(lines_adjacency) in;
layout(triangle_strip, max_vertices = 4) out;

layout(location = 0) in data
{
  vec2 sensorPos;
}vert[4];

out data
{
  vec2 sensorout;
};


void main()
{
  gl_Position = gl_in[0].gl_Position;
  sensorout = vert[0].sensorPos;
  EmitVertex();
  gl_Position = gl_in[1].gl_Position;
  sensorout = vert[1].sensorPos;
  EmitVertex();
  gl_Position = gl_in[2].gl_Position;
  sensorout = vert[2].sensorPos;
  EmitVertex();
  gl_Position = gl_in[3].gl_Position;
  sensorout = vert[3].sensorPos;
  EmitVertex();

  EndPrimitive();
}
