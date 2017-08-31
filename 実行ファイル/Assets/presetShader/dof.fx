/*!
 * @brief	��ʊE�[�x�B
 */



texture g_depthTexture;	//�[�x�e�N�X�`���B
float2 g_rtSize;		//�����_�����O�^�[�Q�b�g�̃T�C�Y�B

float2 g_nearFar;
sampler g_depthSampler = 
sampler_state
{
	Texture = <g_depthTexture>;
    MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float3 g_dofParam;		//
texture g_blurBack;	//���{�P
sampler g_blurBackSampler = 
sampler_state
{
	Texture = <g_blurBack>;
    MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture g_blurForward;	//��O�{�P
sampler g_blurForwardSampler = 
sampler_state
{
	Texture = <g_blurForward>;
    MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


struct VS_INPUT{
	float4	pos : POSITION;
};

struct VS_OUTPUT{
	float4 pos 	: POSITION;
	float2 tex0 : TEXCOORD0;
};
/*!
 * @brief	���_�V�F�[�_�B
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
	
	tex.y = 1.0f - tex.y;
	Out.tex0 = tex + float2( 0.5/g_rtSize.x, 0.5/g_rtSize.y);
	return Out;
}

/*!
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain(VS_OUTPUT In ) : COLOR
{
	float4 depth = tex2D(g_depthSampler, In.tex0 + float2(0.5f/g_rtSize.x,0.0f));
	depth = min( depth, tex2D(g_depthSampler, In.tex0 + float2(-0.5f/g_rtSize.x,0.0f) ) );
	depth = min( depth, tex2D(g_depthSampler, In.tex0 + float2(0.0f,-0.5f/g_rtSize.y) ) );
	depth = min( depth, tex2D(g_depthSampler, In.tex0 + float2(0.0f,0.5f/g_rtSize.y) ) );
	
	//��O�{�P
	float alpha = depth - g_dofParam.z;
	float forwardRate = max( 0.0f, -g_dofParam.x - alpha );
	float backRate = max(0.0f, alpha - g_dofParam.y);
	alpha = max(forwardRate, backRate);
	alpha = alpha / ((g_dofParam.z- g_dofParam.x));
	float4 color = 0.0f;
	if(forwardRate < backRate){
		//���{�P
		alpha *= g_dofParam.x / (g_dofParam.y);
		alpha = min(1.0f, alpha);
		float4 blur = tex2D(g_blurBackSampler, In.tex0);
		color = float4(blur.xyz, alpha);

	}else{
		//��O�{�P
		alpha = min(1.0f, alpha * 2.0f);
		float4 blur = tex2D(g_blurForwardSampler, In.tex0);
		color = float4(blur.xyz, alpha);
	}
	
	return color;
}
/*!
 * @brief	��O�{�P�Ɖ��{�P�̍����e�N�j�b�N�B
 */
technique CombineBackForwardBoke
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
