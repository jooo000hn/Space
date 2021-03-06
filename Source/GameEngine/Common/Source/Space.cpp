#include "stdafx.h"
#include "Space.h"
using namespace SpaceGameEngine;

tstring SpaceGameEngine::StringToTString(const std::string & str)
{
	tstring tstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), tstr.begin());
	return tstr;
}

std::string SpaceGameEngine::TStringToString(const tstring & tstr)
{
	std::string str;
	for (auto i : tstr)
	{
		str += i;
	}
	return str;
}

float SpaceGameEngine::GetDeltaTime()
{
	static float TimeNow=0.00f;
	static float TimeBuffer = 0.00f;
	static float DeltaTime = 0.00f;
	if (TimeNow == 0.00f)
	{
		TimeNow = timeGetTime()*0.001f;
		return SpaceGameEngine::GetDeltaTime();
	}
	else
	{
		TimeBuffer = timeGetTime()*0.001f;
		DeltaTime = TimeBuffer - TimeNow;
		TimeNow = timeGetTime()*0.001f;
		return DeltaTime;
	}
}

void SpaceGameEngine::ThrowError(const tstring & errormessege)
{
	MessageBox(NULL, errormessege.c_str(), L"Space Game Engine", NULL);
}

std::vector<std::pair<std::string, std::string> > SpaceGameEngine::ReadAssetListFromFile(const std::string & filename)
{
	std::vector<std::pair<std::string, std::string> > re;
	std::fstream file(filename, std::ios::in);
	std::string componentname, assetname;

	while (file >> componentname >> assetname)
	{
		re.push_back(make_pair(componentname, assetname));
	}
	file.close();

	return re;
}

void SpaceGameEngine::SetDefaultInputLayout(ID3D11Device* device, ID3DBlob* ShaderByteCode,ID3D11InputLayout** inputlayout)
{
	static D3D11_INPUT_ELEMENT_DESC indesc[]=
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	device->CreateInputLayout(indesc, 3, ShaderByteCode->GetBufferPointer(), ShaderByteCode->GetBufferSize(), inputlayout);
}

void SpaceGameEngine::CompileShaderFromFile(LPCWSTR filename,const std::string& includefilename, const std::string & entryname, const std::string & target, D3D_SHADER_MACRO* macros,ID3DBlob ** ShaderByteCode)
{
	ID3DBlob* errormsg;
	LPCSTR sourcefile = includefilename.empty() == true ? NULL : includefilename.c_str();
	ID3DInclude* include = includefilename.empty() == true ? NULL : ((ID3DInclude*)(UINT_PTR)1);
	D3DCompileFromFile(filename, macros, include, entryname.c_str(), target.c_str(), 0, 0, ShaderByteCode, &errormsg);
}
