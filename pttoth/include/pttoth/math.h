/*
 * -------------------------------------------------------------------------
 * FILE:    math.h
 * AUTHOR:  Dr. Szécsi László - szecsi@iit.bme.hu
 *          Peter Toth - peter.t.toth92@gmail.com  (minor modifications)
 * -------------------------------------------------------------------------
 */

#pragma once

#include <cmath>
#include <cstdlib>
#include <stdexcept>

//#pragma warning( disable : 4201 )
//#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
//#pragma GCC diagnostic ignored "-Wnested-anon-types"
//#pragma GCC diagnostic ignored "-Wtautological-unsigned-zero-compare"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "math/boolswizzle.h"
#include "math/bool1.h"
#include "math/bool2.h"
#include "math/bool3.h"
#include "math/bool4.h"

#include "math/intswizzle.h"
#include "math/int1.h"
#include "math/int2.h"
#include "math/int3.h"
#include "math/int4.h"

#include "math/floatswizzle.h"
#include "math/float2swizzle.h"
#include "math/float3swizzle.h"
#include "math/float4swizzle.h"
#include "math/float1.h"
#include "math/float2.h"
#include "math/float3.h"
#include "math/float4.h"

#include "math/float4x4.h"

#pragma GCC diagnostic warning "-Wreturn-type"
#pragma GCC diagnostic warning "-Wtype-limits"
#pragma GCC diagnostic warning "-Wunused-value"
//#pragma GCC diagnostic warning "-Wtautological-unsigned-zero-compare"
//#pragma GCC diagnostic warning "-Wnested-anon-types"
//#pragma GCC diagnostic warning "-Wgnu-anonymous-struct"
//#pragma warning( enable : 4201 )
