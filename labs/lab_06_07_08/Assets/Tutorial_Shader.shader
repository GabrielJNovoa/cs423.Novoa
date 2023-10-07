Shader"Unlit/Tutorial_Shader"
{
    Properties
    {
        _Color ("Set the color", Color) = (1,1,1,1)
        _MainTexture("Main Texture", 2D) = "white" {}
        _DissolveTexture ("Dissolve Texture", 2D) = "white" {}
        _DissolveCutoff ("Dissolve Cutoff", Range(0,1)) = 1
    }

    SubShader
    {
        Pass
        {
            CGPROGRAM
                #pragma vertex vert
                #pragma fragment frag
                #include "UnityCG.cginc"
                struct appdata {
                    float4 vertex: POSITION;
                    float2 uv : TEXCOORD0;
                };
                struct v2f {
                    float4 position : SV_POSITION;
                    float2 uv : texCOORD0;
                };

                float4 _Color;
                float _DissolveCutoff;
                sampler2D _MainTexture;
                sampler2D _DissolveTexture;

                v2f vert(appdata inbound) {
                    v2f outbound;
                    outbound.position = UnityObjectToClipPos(inbound.vertex.xyz);
                    outbound.uv = inbound.uv;
                    return outbound;
                }
                fixed4 frag(v2f inbound) : SV_Target {
                    float4 textureColor = tex2D(_MainTexture, inbound.uv);
                    float4 dissolveColor = tex2D(_DissolveTexture, inbound.uv);
                    clip(_DissolveCutoff - (dissolveColor.x + dissolveColor.y + dissolveColor.z));
                    return textureColor * _Color;
                }
            ENDCG
        }
    }
}
