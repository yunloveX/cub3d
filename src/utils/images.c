/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nulsuga <nulsuga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/05 10:43:20 by nulsuga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void blend_images(mlx_image_t *dst, mlx_texture_t *src, int x, int y, int frame, int scale)
{
    int frames_per_row = 5; // 10 frames in two rows means 5 frames per row
    int frame_width = src->width / frames_per_row;
    int frame_height = src->height / 2; // Two rows

    int frame_row = frame / frames_per_row;
    int frame_col = frame % frames_per_row;

    // Clear the destination image
    memset(dst->pixels, 0, dst->width * dst->height * sizeof(uint32_t));

    for (int i = 0; i < frame_width; i++) {
        for (int j = 0; j < frame_height; j++) {
            int src_x = frame_col * frame_width + i;
            int src_y = frame_row * frame_height + j;

            uint8_t *src_pixel = &src->pixels[(src_y * src->width + src_x) * 4];
            uint32_t color = color_from_mem(src_pixel);

            if (color & 0xFF000000) { // Check alpha
                int dst_x = x + i * scale;
                int dst_y = y + j * scale;
                for (int si = 0; si < scale; si++) {
                    for (int sj = 0; sj < scale; sj++) {
                        if (dst_x + si < dst->width && dst_y + sj < dst->height) {
                            mlx_put_pixel(dst, dst_x + si, dst_y + sj, color);
                        }
                    }
                }
            }
        }
    }
}

void sprite(t_cub3d *cub3d)
{
    // Define a scaling factor
    double scale = 2.0; // Example: scale by 2x

    // Calculate animation frame
    int frame = (int)(cub3d->hand_animation_frame) % 10;

    // Calculate sprite position (bottom center)
    int frames_per_row = 5; // 10 frames in two rows means 5 frames per row
    int frame_width = cub3d->textures[4]->width / frames_per_row;
    int frame_height = cub3d->textures[4]->height / 2; // Two rows

    // Apply scaling
    int scaled_frame_width = frame_width * scale;
    int scaled_frame_height = frame_height * scale;

    int x_pos = WIDTH / 2 - scaled_frame_width / 2;
    int y_pos = HEIGHT - scaled_frame_height + 15;

    // Create a new image
	if (!cub3d->img_hands)
		cub3d->img_hands = mlx_new_image(cub3d->mlx, scaled_frame_width, scaled_frame_height);

    // Draw current frame with scaling onto the new image
    blend_images(cub3d->img_hands, cub3d->textures[4], 0, 0, frame, scale);

    // Put the new image to the window
    mlx_image_to_window(cub3d->mlx, cub3d->img_hands, x_pos, y_pos);

    // Advance animation if playing
    if (cub3d->hand_animation_playing)
    {
        cub3d->hand_animation_frame += 0.65;
        if (cub3d->hand_animation_frame >= 10.0) {
            memset(cub3d->img_hands->pixels, 0, cub3d->img_hands->width * cub3d->img_hands->height * sizeof(uint32_t));
            mlx_image_to_window(cub3d->mlx, cub3d->img_hands, x_pos, y_pos);
            cub3d->hand_animation_playing = 0;
        }
            
    }
}
