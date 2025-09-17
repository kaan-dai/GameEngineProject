//--------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

// DirectX includes
#include <d3d11.h>
#include <d3dcompiler.h>

#include "Game.h"
#include "File.h"
#include "StateDepthStencil.h"

namespace Azul
{
	extern unsigned int NumIndices;

	void Game::SetDefaultTargetMode()
	{
		//--------------------------------------------------------
		// Set Rasterizers functions to be used
		//--------------------------------------------------------
		this->mStateRasterizerSolid.Activate();

		//--------------------------------------------------------
		// Set Viewport to be used
		//--------------------------------------------------------
		this->mViewport.Activate();

		//--------------------------------------------------------
		// Set render target
		//      Only one Target, this maps to Pixel shader
		// --------------------------------------------------------
		this->mStateRenderTargetView.Activate(this->mDepthStencilView);

		//--------------------------------------------------------
		// Set blend target
		//--------------------------------------------------------
		this->mBlendStateOff.Activate();

		//--------------------------------------------------------
		// Set Depth functions to be used
		//--------------------------------------------------------
		this->mStateDepthStencil.Activate();
	}

	float Game::GetAspectRatio() const
	{
		float ratio = (float) mWindowWidth / (float) mWindowHeight;

		return ratio;
	}

}

// --- End of File ---
