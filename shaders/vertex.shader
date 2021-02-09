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

in vec2                 pos;

void                    main(void)
{
    gl_Position = vec4(pos, 0.0f, 1.0f);
}
