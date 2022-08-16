#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;

uniform vec4 outColor;
uniform sampler2D texSampler;
uniform sampler2D texSampler2;
uniform float alpha;

void main()
{
    // FragColor = mix(texture(texSampler, texCoord), texture(texSampler2, texCoord), 0.2);

    // 练习1： 修改片段着色器，仅让笑脸图案朝另一个方向看
    // FragColor = mix(texture(texSampler, texCoord), 
    //                 texture(texSampler2, vec2(1-texCoord.x, texCoord.y)), 0.2);


    // 练习4： 使用一个uniform变量作为mix函数的
    //        第三个参数来改变两个纹理可见度，
    //        使用上和下键来改变箱子或笑脸的可见度：
    FragColor = mix(texture(texSampler, texCoord), 
                    texture(texSampler2, vec2(1-texCoord.x, texCoord.y)), alpha);

}