/* *********************************** */
/*                                     */
/*      Lem-in project                 */
/*                                     */
/*      Created by Artur Makhnach      */
/*      github.com/DippyArtu           */
/*      artum.me                       */
/*                                     */
/* *********************************** */

#version 150 core

in vec3 fColor;

out vec4 outColor;

void main()
{
    outColor = vec4(fColor, 1.0);
}