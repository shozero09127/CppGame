varying vec4 v_color;//(入力)色

void main()
{
// シェーダの出力にカラーをコピー
gl_FragColor = v_color;
}