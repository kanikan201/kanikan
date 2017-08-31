/*!
 *@brief	�g�[���}�b�v�B
 */

struct VS_INPUT{
	float4	pos : POSITION;
};
struct VS_OUTPUT{
	float4 pos : POSITION;
	float2  tex : TEXCOORD;
};

static const int    MAX_SAMPLES            = 16;    // Maximum texture grabs
float2 g_avSampleOffsets[MAX_SAMPLES];
// The per-color weighting to be used for luminance calculations in RGB order.
static const float3 LUMINANCE_VECTOR  = float3(0.2125f, 0.7154f, 0.0721f);


texture g_scene;	//�V�[���e�N�X�`���B
sampler g_SceneSampler = 
sampler_state
{
    Texture = <g_scene>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

texture g_lumAvgTex;	//�P�x�̕��ϒl���i�[����1�~1�̃e�N�X�`���B
sampler g_lumAvgSampler = 
sampler_state
{
	Texture = <g_lumAvgTex>;
	MipFilter = POINT;
    MinFilter = POINT;
    MagFilter = POINT;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

texture g_lastLumAvgTex;	//��t���[���O�̋P�x�̕��ϒl���i�[����1�~1�̃e�N�X�`���B
sampler g_lastLumAvgSampler = 
sampler_state
{
	Texture = <g_lastLumAvgTex>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
float  g_fMiddleGray;       // The middle gray key value
float g_fElapsedTime;
/*!
 *@brief	���_�V�F�[�_�[�B
 */
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;		//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.tex = (In.pos * 0.5f) + 0.5f;
	Out.tex.y = 1.0f - Out.tex.y;
	return Out;
}
/*!
 *@brief	�P�x�̑ΐ����ς����߂�B
 */
float4 PSCalcLuminanceLogAvarage(VS_OUTPUT In) : COLOR
{
	 float3 vSample = 0.0f;
    float  fLogLumSum = 0.0f;

    for(int iSample = 0; iSample < 9; iSample++)
    {
        // Compute the sum of log(luminance) throughout the sample points
        vSample = tex2D(g_SceneSampler, In.tex+g_avSampleOffsets[iSample]);
        fLogLumSum += log(dot(vSample, LUMINANCE_VECTOR)+0.0001f);
    }
    
    // Divide the sum to complete the average
    fLogLumSum /= 9;

    return float4(fLogLumSum, fLogLumSum, fLogLumSum, 1.0f);
}
/*!
 *@brief	���ϋP�x�v�Z�s�N�Z���V�F�[�_�[�B
 */
float4 PSCalcLuminanceAvarage(VS_OUTPUT In) : COLOR
{
	float fResampleSum = 0.0f; 
    
    for(int iSample = 0; iSample < 16; iSample++)
    {
        // Compute the sum of luminance throughout the sample points
        fResampleSum += tex2D(g_SceneSampler, In.tex+g_avSampleOffsets[iSample]);
    }
    
    // Divide the sum to complete the average
    fResampleSum /= 16;

    return float4(fResampleSum, fResampleSum, fResampleSum, 1.0f);
}
/*!
 *@brief	�w���֐����g�p���ĕ��ϋP�x�����߂�s�N�Z���V�F�[�_�[�B
 */
float4 PSCalcLuminanceExpAvarage( VS_OUTPUT In ) : COLOR
{
	float fResampleSum = 0.0f;
    
    for(int iSample = 0; iSample < 16; iSample++)
    {
        // Compute the sum of luminance throughout the sample points
        fResampleSum += tex2D(g_SceneSampler, In.tex+g_avSampleOffsets[iSample]);
    }
    
    // Divide the sum to complete the average, and perform an exp() to complete
    // the average luminance calculation
    fResampleSum = exp(fResampleSum/16);
    
    return float4(fResampleSum, fResampleSum, fResampleSum, 1.0f);
}
/*!
 *@brief	���Ï����̂��߂̕��ϋP�x�̓K��������s�N�Z���V�F�[�_�[�B
 */
float4 PSCalcAdaptedLuminance( VS_OUTPUT In ) : COLOR
{
	float fAdaptedLum = tex2D(g_lastLumAvgSampler, float2(0.5f, 0.5f));
    float fCurrentLum = tex2D(g_lumAvgSampler, float2(0.5f, 0.5f));
    
    // The user's adapted luminance level is simulated by closing the gap between
    // adapted luminance and current luminance by 2% every frame, based on a
    // 30 fps rate. This is not an accurate model of human adaptation, which can
    // take longer than half an hour.
    float fNewAdaptation = fAdaptedLum + (fCurrentLum - fAdaptedLum) * ( 1 - pow( 0.98f, 60 * g_fElapsedTime ) );
    return float4(fNewAdaptation, fNewAdaptation, fNewAdaptation, 1.0f);
}
float4 PSCalcAdaptedLuminanceFirst(VS_OUTPUT In) : COLOR
{
	float fAvgLum = tex2D(g_lumAvgSampler, float2(0.5f, 0.5f));
	return float4(fAvgLum, fAvgLum, fAvgLum, 1.0f);
}
/*!
 *@brief	���ϋP�x����g�[���}�b�v���s���s�N�Z���V�F�[�_�[�B
 */
float4 PSFinal( VS_OUTPUT In) : COLOR
{
	float4 vSample = tex2D(g_SceneSampler, In.tex);
	float fAvgLum = tex2D(g_lumAvgSampler, float2( 0.5f, 0.5f));
	
	vSample.rgb *= g_fMiddleGray/(fAvgLum + 0.001f);
//	vSample.rgb /= (1.0f+vSample);
	return vSample;
}
/*!
 *@brief	���ϋP�x��ΐ����ςŋ��߂�B
 */
technique CalcLuminanceLogAvarage{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSCalcLuminanceLogAvarage();
	}
}
/*!
 *@brief	�_�E���T���v�����O���s���ċP�x�̕��ς����߂�e�N�j�b�N�B
 */
technique CalcLuminanceAvarage{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSCalcLuminanceAvarage();
	}
}
/*!
 *@brief	exp�֐����g�p���ċP�x�̕��ϒl�����߂�e�N�j�b�N�B
 */
technique CalcLuminanceExpAvarage{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSCalcLuminanceExpAvarage();
	}
}
/*!
 *@brief	���Ï����̂��߂̕��ϋP�x�̓K�������B
 *@details
 * ���Ԃɉ����ĕ��ϋP�x��K�������܂��B
 */
technique CalcAdaptedLuminance{
	pass p0{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSCalcAdaptedLuminance();
	}
}
/*!
 *@brief	�V�[�����؂�ւ���Ĉ��ڂ̕`��̎��ɂ����g�p���閾�Ï����̂��߂̏����B
 */
technique CalcAdaptedLuminanceFirst{		
	pass p0{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSCalcAdaptedLuminanceFirst();
	}
}
/*!
 *@brief	�ŏI�e�N�j�b�N�B
 *@details
 * �����܂łŋ��߂����ϋP�x����g�[���}�b�v���s���B
 */
technique Final{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSFinal();
	}
}