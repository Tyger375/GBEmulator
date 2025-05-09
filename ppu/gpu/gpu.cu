#include <cuda_runtime.h>
#include <cstdio>
#include <SDL3/SDL_stdinc.h>
#include "../../defs.hpp"
#include "gpu.cuh"

__device__ unsigned int mapRGB(unsigned char r, unsigned char g, unsigned char b) {
    // Assume RGB888 format (8 bits per channel)
    return (r << 16) | (g << 8) | b;
}

__device__ Uint32 color_to_rgb(Byte color) {
    switch (color) {
        case 0: {
            return mapRGB(255, 255, 255);
        }
        case 1: {
            return mapRGB(169, 169, 169);
        }
        case 2: {
            return mapRGB(84, 84, 84);
        }
        case 3: {
            return mapRGB(0, 0, 0);
        }
        default: return mapRGB(255, 255, 255);
    }
}

__global__ void cuda_build_video(
        Byte* video,
        Uint32* scaled_video,
        int scale
        ) {
    u32 pos = blockIdx.y * DISPLAY_WIDTH + blockIdx.x;
    u32 scaled_pos = (blockIdx.y * scale + threadIdx.y) * (DISPLAY_WIDTH * scale) + (blockIdx.x * scale + threadIdx.x);
    scaled_video[scaled_pos] = color_to_rgb(video[pos]);
}

void prepare_pointers(
        Byte** device_video,
        size_t* pitch,
        Uint32** device_scaled_video,
        size_t* scaled_pitch,
        u32 width,
        u32 height,
        int scale
        ) {
    cudaMallocPitch((void**)device_video, pitch, width * sizeof(Byte), height);

    u32 new_width = width * scale;
    u32 new_height = height * scale;

    cudaMallocPitch((void**)device_scaled_video, scaled_pitch, new_width * sizeof(Uint32), new_height);
}

void free_pointers(Byte* video, Uint32* scaled_video) {
    cudaFree(video);
    cudaFree(scaled_video);
}

void build_video(
        Byte* device_video,
        Uint32* device_scaled_video,
        Byte* video,
        Uint32* scaled_video,
        u32 width,
        u32 height,
        int scale
) {
    u32 new_width = width * scale;
    u32 new_height = height * scale;


    cudaMemcpy(
            device_video,
            video,
            (width * height) * sizeof(Byte),
            cudaMemcpyHostToDevice
            );

    dim3 video_dim(width, height);
    dim3 scale_dim(scale, scale);
    cuda_build_video<<<video_dim, scale_dim>>>(device_video, device_scaled_video, scale);

    cudaMemcpy(
            scaled_video,
            device_scaled_video,
            (new_width * new_height) * sizeof(Uint32),
            cudaMemcpyDeviceToHost
    );
}