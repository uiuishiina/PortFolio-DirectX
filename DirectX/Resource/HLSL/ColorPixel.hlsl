#include"StructHeader.hlsli"

PS_OutPut main(VS_OutPutColor input)
{
    PS_OutPut output;
	
    output.color = input.color;
    
    return output;
}