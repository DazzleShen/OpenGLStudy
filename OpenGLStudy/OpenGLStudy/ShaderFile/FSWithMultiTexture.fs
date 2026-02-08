#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //vec4 tex1 = texture(texture1, TexCoord);
    //vec4 tex2 = texture(texture2, Texcoord) * vec4(1.0, 1.0, 1.0, 1.0);
    //FragColor = mix(tex1, tex2, 0.2);
    //FragColor = texture(texture2, TexCoord);// * vec4(ourColor, 1.0);
    //FragColor = mix(tex1, FragColor, 0.2);

    // face to another direct
    //vec2 face = TexCoord;
    //face.x = -face.x;
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, face), 0.8);
}