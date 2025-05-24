attribute vec3 a_posL;
attribute vec3 a_color;

uniform mat4 uMVP;

varying vec3 v_color;

void main()
{
    v_color = a_color;
    gl_Position = uMVP * vec4(a_posL, 1.0);
}
