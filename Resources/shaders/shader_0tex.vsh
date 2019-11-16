attribute vec4 a_position;//(入力)座標
attribute vec4 a_color;//(入力)色
varying vec4 v_color;//(出力)座標
//頂点シェーダ
void main()
{
	//シェーダの出力に座標をコピー
	gl_Position = a_position;
	//入力から出力に色をコピー
	v_color = a_color;
}