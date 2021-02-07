/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#version 330 core

in vec3 pos;
in vec3 color;

out vec3 vColor;

void main()
{
    gl_Position = vec4(pos, 1.0);
    vColor = color;
}