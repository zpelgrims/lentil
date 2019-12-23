#version 450

#define SIZE 16

layout (binding = 0, rg16f) uniform image2DArray src;
layout (binding = 1, rg16f) uniform image2DArray dst;

layout (local_size_x = SIZE, local_size_y = SIZE, local_size_z = 1) in;

void main()
{
  ivec3 dstPos = ivec3(gl_GlobalInvocationID);
  ivec3 srcPos = ivec3(2*dstPos.xy, dstPos.z);
  if(any(greaterThan(dstPos.xy, imageSize(dst).xy)))
    return;
  if(any(greaterThan(srcPos.xy, imageSize(src).xy)))
    return;

  vec4 val = vec4(1e7, 0, 0, 0);
  vec4 texel[4];
  ivec3 off = ivec3(0);
  texel[0] = imageLoad(src, srcPos+off);
  off.xy = ivec2(0, 1);
  texel[1] = imageLoad(src, srcPos+off);
  off.xy = ivec2(1, 1);
  texel[2] = imageLoad(src, srcPos+off);
  off.xy = ivec2(1, 0);
  texel[3] = imageLoad(src, srcPos+off);

  for(int i = 0; i < 4; i++)
    val.r = min(val.r, texel[i].r);
  for(int i = 0; i < 4; i++)
    val.g = max(val.g, texel[i].g);

  imageStore(dst, dstPos, val);
}

