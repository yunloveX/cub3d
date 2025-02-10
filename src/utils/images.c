/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:30:25 by yunlovex          #+#    #+#             */
/*   Updated: 2025/02/10 11:06:41 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void blend_images(mlx_image_t *dst, mlx_texture_t *src, int scale)
{
    uint8_t *src_pixel;
    uint32_t color;

    // Clear the destination image
    memset(dst->pixels, 0, dst->width * dst->height * sizeof(uint32_t));

    for (int i = 0; i < src->width; i++) {
        for (int j = 0; j < src->height; j++) {
            uint8_t *src_pixel = &src->pixels[(j * src->width + i) * 4];
            uint32_t color = color_from_mem(src_pixel);

            if (color & 0xFF000000) { // Check alpha
                int dst_x = i * scale;
                int dst_y = j * scale;
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
    mlx_texture_t *frame;

    frame = cub3d->hand_frame->content;
    
    // Apply scaling
    int scaled_frame_width = frame->width * SCALE;
    int scaled_frame_height = frame->height * SCALE;

    int x_pos = WIDTH / 2 - scaled_frame_width / 2;
    int y_pos = HEIGHT - scaled_frame_height + 15;

    // Draw current frame with scaling onto the new image
    blend_images(cub3d->img_hands, frame, SCALE);

    // Put the new image to the window
    mlx_image_to_window(cub3d->mlx, cub3d->img_hands, x_pos, y_pos);

    // Advance animation if playing
    if (cub3d->hand_playing)
    {
        cub3d->hand_frame = cub3d->hand_frame->next;
        if (cub3d->hand_frame == NULL) {
            memset(cub3d->img_hands->pixels, 0, cub3d->img_hands->width * cub3d->img_hands->height * sizeof(uint32_t));
            mlx_image_to_window(cub3d->mlx, cub3d->img_hands, x_pos, y_pos);
            cub3d->hand_frame = *(cub3d->hand_texture);
        }
            
    }
}
