#version 330


in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;





float distance_to_nearest_floor(float a, float b){
    return max(abs(a - (floor(a / b) * b)), 0);
}


vec4 get_color(vec2 fragment_texture_coord, vec2 pixel_size, vec4 color){
    vec2 output_position = fragment_texture_coord;
    output_position.x = output_position.x - distance_to_nearest_floor(output_position.x, pixel_size.x);
    output_position.y = output_position.y - distance_to_nearest_floor(output_position.y, pixel_size.y);

    
    float distance_left = distance_to_nearest_floor(fragment_texture_coord.x, pixel_size.x);
    float distance_top = distance_to_nearest_floor(fragment_texture_coord.y, pixel_size.y);
    float half_width = pixel_size.x / 2;
    float half_height = pixel_size.y / 2;

    bool left_side = distance_left < half_width;
    bool top_side = distance_top < half_height;
    

    vec4 top_color = texture(texture0, vec2(output_position.x, output_position.y - pixel_size.y)) * color;
    vec4 bottom_color = texture(texture0, vec2(output_position.x, output_position.y + pixel_size.y)) * color;
    vec4 right_color = texture(texture0, vec2(output_position.x + pixel_size.x, output_position.y)) * color;
    vec4 left_color = texture(texture0, vec2(output_position.x - pixel_size.x, output_position.y)) * color;
    vec4 this_color = texture(texture0, output_position) * color;

    vec4 out_color = this_color;
    

    
         
    if (left_side && top_side){
        if (left_color == top_color){
            out_color = left_color;
        }
    }else if (!left_side && top_side){
        if (right_color == top_color){
            out_color = top_color;
        }
    }else if (left_side && !top_side){
        if (left_color == bottom_color){
            out_color = bottom_color;
        }
    }else if (!left_side && !top_side){
        if (right_color == bottom_color){
            out_color = bottom_color;
        }
    }

    if ((int(left_color == top_color)
     + int(top_color == right_color)
     + int(right_color == bottom_color)
     + int(bottom_color == left_color)
     + int(left_color == right_color)
     + int(top_color == bottom_color)
     ) >= 3){
        out_color = this_color;
    }

    
    return out_color;
}




void main(){
    ivec2 size = textureSize(texture0, 0);
    vec2 pixel_size = vec2((1.0 / size.x), (1.0 / size.y)); // fix wierd rounding error



    gl_FragColor = get_color(fragTexCoord, pixel_size, fragColor);
}