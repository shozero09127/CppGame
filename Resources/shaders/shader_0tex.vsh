attribute vec4 a_position;//(����)���W
attribute vec4 a_color;//(����)�F
varying vec4 v_color;//(�o��)���W
//���_�V�F�[�_
void main()
{
	//�V�F�[�_�̏o�͂ɍ��W���R�s�[
	gl_Position = a_position;
	//���͂���o�͂ɐF���R�s�[
	v_color = a_color;
}