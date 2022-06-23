
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind/ncbind.hpp"
#include "LayerBitmapUtility.h"

#if 0
static tjs_error TJS_INTF_METHOD
drawAATriangle(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 100090E0 10002350 not used
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	//arg0 = tTJSVariant::AsObjectNoAddRef
	//arg1 = tTVInteger tTJSVariant::AsInteger() const
	//arg2 = tTVInteger tTJSVariant::AsInteger() const
	//arg3 = tTVInteger tTJSVariant::AsInteger() const
	//arg4 = tTVInteger tTJSVariant::AsInteger() const
	//arg5 = tTVInteger tTJSVariant::AsInteger() const
	//arg6 = tTVInteger tTJSVariant::AsInteger() const
	//arg7 = tTVInteger tTJSVariant::AsInteger() const
	return TJS_E_NOTIMPL;
}
#endif

static struct
{
	tjs_uint32 *buffer;
	tjs_int pitch, width, height;
	tjs_int width_minus_one, height_minus_one;
} line_vars;

static tjs_int32 sub_10001000(int x, int y)
{
	tjs_int32 result;

	result = 0;
	if ( x >= 0 )
	{
		if ( x > line_vars.width_minus_one )
			result = 2;
	}
	else
	{
		result = 1;
	}
	if ( y >= 0 )
	{
		if ( y > line_vars.height_minus_one )
			result += 8;
	}
	else
	{
		result += 4;
	}
	return result;
}

static tjs_int32 sub_10001050(char a1, int x1, int y1, int x2, int y2, int *x_out, int *y_out)
{
	int v7;
	tjs_int32 result;
	int v9;
	int v10;
	int v11;

	if ( a1 & 1 && (v7 = y1 + (y2 - y1) * (0 - x1) / (x2 - x1), v7 >= 0) && v7 <= line_vars.height_minus_one )
	{
		x_out[0] = 0;
		y_out[0] = v7;
		result = 1;
	}
	else if ( a1 & 2
				 && (v9 = y1 + (y2 - y1) * (line_vars.width_minus_one - x1) / (x2 - x1), v9 >= 0)
				 && v9 <= line_vars.height_minus_one )
	{
		x_out[0] = line_vars.width_minus_one;
		y_out[0] = v9;
		result = 1;
	}
	else if ( a1 & 4
				 && (v10 = x1 + (x2 - x1) * (0 - y1) / (y2 - y1), v10 >= 0)
				 && v10 <= line_vars.width_minus_one )
	{
		x_out[0] = v10;
		y_out[0] = 0;
		result = 1;
	}
	else if ( a1 & 8
				 && (v11 = x1 + (x2 - x1) * (line_vars.height_minus_one - y1) / (y2 - y1), v11 >= 0)
				 && v11 <= line_vars.width_minus_one )
	{
		x_out[0] = v11;
		y_out[0] = line_vars.height_minus_one;
		result = 1;
	}
	else
	{
		result = -1;
	}
	return result;
}

static tjs_int32 sub_100011A0(int *x1, int *y1, int *x2, int *y2)
{
	tjs_int32 v5;
	tjs_int32 result;
	tjs_int32 v7;

	v5 = sub_10001000(x1[0], y1[0]);
	result = sub_10001000(x2[0], y2[0]);
	v7 = result;
	if ( v5 || result )
	{
		if ( result & v5 )
			return -1;
		if ( v5 )
		{
			if ( sub_10001050(v5, x1[0], y1[0], x2[0], y2[0], x1, y1) < 0 )
				return -1;
			result = v7;
		}
		if ( result && sub_10001050(result, x1[0], y1[0], x2[0], y2[0], x2, y2) < 0 )
			result = -1;
		else
			result = 1;
	}
	return result;
}

static void sub_10001260(tjs_uint32 *a1, int a2, int a3, int a4)
{
	line_vars.buffer = a1;
	line_vars.pitch = a2;
	line_vars.width = a3;
	line_vars.height = a4;
	line_vars.width_minus_one = a3 - 1;
	line_vars.height_minus_one = a4 - 1;
}

void sub_100014A0(int x1, int y1, int x2, int y2, tjs_uint32 color)
{
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v20;
	int v21;
	int v23;
	int v24;
	tjs_uint16 v25;
	int v26;
	int v27;
	int v28;
	int v29;
	int v30;
	int v31;
	int v33;
	int v34;
	int v35;
	int v37;
	int v38;
	int v39;
	int v40;
	int v41;
	int v42;
	int v43;
	int v44;
	int v45;
	int v46;
	int v47;

	v31 = line_vars.pitch >> 2;
	if ( x2 <= x1 )
	{
		v39 = x1 - x2;
		v7 = x1 - x2;
	}
	else
	{
		v7 = x2 - x1;
		v39 = x2 - x1;
	}
	if ( y2 <= y1 )
		v8 = y1 - y2;
	else
		v8 = y2 - y1;
	v9 = x1 << 16;
	v10 = x2 << 16;
	v11 = y1 << 16;
	v12 = y2 << 16;
	v43 = v8;
	if ( v7 >= v8 )
	{
		if ( !v7 )
			v39 = 1;
		v14 = ((y2 << 16) - (y1 << 16)) / v39;
		v23 = ((v10 - v9) >> 31) | 1;
		v34 = y1 << 16;
		v24 = v9 >> 16;
		v37 = v23;
		v42 = v24;
		v38 = ((y2 << 16) - v11) / v39;
		if ( v39 )
		{
			v25 = color;
			v47 = (color >> 16) & 0xFF;
			v14 = v25 >> 8;
			v40 = (tjs_uint8)v25;
			for (int i = 0; i < v39; i += 1)
			{
				v26 = v24 + v31 * (v11 >> 16);
				v11 = (tjs_uint16)v11;
				v45 = v26 + v31;
				v27 = line_vars.buffer[v26];
				line_vars.buffer[v26] = (((v14 + (v11 * (((v27 >> 8) & 0xFF) - v14) >> 16)) | ((((tjs_uint8)(v11 * ((tjs_uint32)(tjs_uint8)(line_vars.buffer[v26] >> 16) - v47) >> 16)
																																												+ (tjs_uint8)v47) | 0xFFFFFF00) << 8)) << 8) | (v40 + (v11 * ((line_vars.buffer[v26] & 0xFF) - v40) >> 16));
				v28 = line_vars.buffer[v26 + v31];
				v29 = (0xFFFF - (tjs_uint16)v11) * (((v28 >> 8) & 0xFF) - v14);
				v26 = (v26 & 0xFFFFFF00) | (v47 + ((0xFFFF - (tjs_uint16)v11) * ((tjs_uint32)(((v28 >> 16) & 0xFF)) - v47) >> 16));
				v30 = (0xFFFF - (tjs_uint16)v11) * ((tjs_uint8)v28 - v40);
				v11 = v38 + v34;
				line_vars.buffer[v45] = (((v14 + (v29 >> 16)) | ((v26 | 0xFFFFFF00) << 8)) << 8) | (v40 + (v30 >> 16));
				v24 = v37 + v42;
				v42 += v37;
				v34 += v38;
			}
		}
	}
	else
	{
		if ( !v8 )
			v43 = 1;
		v44 = v9;
		v13 = ((v12 - (y1 << 16)) >> 31) | 1;
		v35 = (v10 - v9) / v43;
		if ( v43 )
		{
			v15 = v31 * (tjs_int16)y1;
			v16 = (color >> 16) & 0xFF;
			v14 = (tjs_uint16)color >> 8;
			v17 = (tjs_uint8)color;
			v33 = v31 * v13;
			v46 = (color >> 16) & 0xFF;
			v41 = v31 * (tjs_int16)y1;
			for (int i = 0; i < v43; i += 1)
			{
				v18 = v15 + (v9 >> 16);
				v19 = (tjs_uint16)v9;
				v20 = line_vars.buffer[v18];
				line_vars.buffer[v18] = (((v14 + (v19 * (((v20 >> 8) & 0xFF) - v14) >> 16)) | ((((tjs_uint8)(v19 * ((tjs_uint32)(tjs_uint8)(line_vars.buffer[v18] >> 16) - v16) >> 16)
																																												+ (tjs_uint8)v16) | 0xFFFFFF00) << 8)) << 8) | (v17 + (v19 * ((line_vars.buffer[v18] & 0xFF) - v17) >> 16));
				v21 = line_vars.buffer[v18 + 1];
				line_vars.buffer[v18 + 1] = (((v14 + ((0xFFFF - v19) * (((v21 >> 8) & 0xFF) - v14) >> 16)) | ((((tjs_uint8)((0xFFFF - v19) * ((tjs_uint32)(tjs_uint8)(line_vars.buffer[v18 + 1] >> 16) - v46) >> 16) + (tjs_uint8)v46) | 0xFFFFFF00) << 8)) << 8) | (v17 + ((0xFFFF - v19) * ((line_vars.buffer[v18 + 1] & 0xFF) - v17) >> 16));
				v9 = v35 + v44;
				v15 = v33 + v41;
				v44 += v35;
				v41 += v33;
				v16 = v46;
			}
		}
	}
}

static tjs_error TJS_INTF_METHOD
drawAALine(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000915C 100021b0; possible replacement by LayerExDraw.drawLine
	if (numparams == 0) return TJS_E_BADPARAMCOUNT;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint32 *dest_buffer;
	// layer: arg0 = tTJSVariant::AsObjectNoAddRef
	iTJSDispatch2 *layer = param[0]->AsObjectNoAddRef();
	// x0: arg1 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int x1 = param[1]->AsInteger();
	// y0: arg2 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int y1 = param[2]->AsInteger();
	// x1: arg3 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int x2 = param[3]->AsInteger();
	// y1: arg4 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int y2 = param[4]->AsInteger();
	// color: arg5 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int color = param[5]->AsInteger();

	//get layer stuff
	tTJSVariant bmpobject = tTJSVariant(layer, layer);
	tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();
	GetBitmapInformationFromObject(bmpobject_clo, true, &dest_width, &dest_height, &dest_pitch, (tjs_uint8 **)&dest_buffer);
	//setting of global variables
	sub_10001260(dest_buffer, dest_pitch, dest_width, dest_height);
	//call sub_100012A0
	if (sub_100011A0(&x1, &y1, &x2, &y2) >= 0)
	{
		sub_100014A0(x1, y1, x2, y2, color);
	}
	//update layer
	UpdateWholeLayerWithLayerObject(bmpobject_clo);
	return TJS_S_OK;
}

static void sub_100012A0(int x1, int y1, int x2, int y2, int color)
{
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v11;
	int v12;
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v20;
	int v21;
	bool v22;
	tjs_int32 v23;
	int v24;
	int v25;
	tjs_int32 v26;
	tjs_int32 v27;
	int v28;
	int v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;

	v27 = x2 <= x1 ? -1 : 1;
	if ( x2 <= x1 )
		v5 = x1 - x2;
	else
		v5 = x2 - x1;
	v6 = y1;
	v7 = y2;
	v24 = v5;
	v26 = y2 <= y1 ? -1 : 1;
	if ( y2 <= y1 )
		v8 = y1 - y2;
	else
		v8 = y2 - y1;
	v9 = line_vars.pitch >> 2;
	v28 = v8;
	if ( v5 < v8 )
	{
		v14 = -v8;
		v15 = v8 + 1;
		v25 = v14;
		v31 = v15;
		v16 = v15 >> 1;
		if ( v15 >> 1 )
		{
			v33 = 2 * v5;
			v17 = y2 * v9;
			v18 = y1 * v9;
			v19 = v26 * v9;
			v34 = v26 * v16 + y1;
			for (int i = 0; i < v16; i += 1)
			{
				v20 = v18 + x1;
				v18 += v19;
				line_vars.buffer[v20] = color;
				v21 = v17 + x2;
				v17 -= v19;
				line_vars.buffer[v21] = color;
				v25 += v33;
				if ( v25 >= 0 )
				{
					x1 += v27;
					x2 -= v27;
					v25 -= 2 * v28;
				}
			}
			v6 = v34;
			v15 = v31;
		}
		v23 = v15 & 0x80000001;
		v22 = v23 == 0;
		if ( v23 < 0 )
			v22 = (((tjs_uint8)v23 - 1) | 0xFFFFFFFE) == 0xFFFFFFFF;
		if ( !v22 )
			goto LABEL_24;
	}
	else
	{
		v11 = -v5;
		v32 = v5 + 1;
		v29 = 2 * v8;
		v12 = v7 * v9;
		v13 = y1 * v9;
		v30 = v26 * v9;
		for (int i = 0; i < ((v5 + 1) >> 1); i += 1)
		{
			line_vars.buffer[v13 + x1] = color;
			line_vars.buffer[v12 + x2] = color;
			x1 += v27;
			x2 -= v27;
			v6 = y1;
			v11 += v29;
			if ( v11 >= 0 )
			{
				v6 = v26 + y1;
				v13 += v30;
				v12 -= v30;
				y1 += v26;
				v11 -= 2 * v24;
			}
		}
		if ( v32 % 2 )
		{
LABEL_24:
			v9 = x1 + v6 * v9;
			line_vars.buffer[v9] = color;
		}
	}
}

static tjs_error TJS_INTF_METHOD
drawLine(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 100091D8 10002010; possible replacement by LayerExDraw.drawLine
	if (numparams < 6) return TJS_E_BADPARAMCOUNT;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint32 *dest_buffer;
	// layer: arg0 = tTJSVariant::AsObjectNoAddRef
	iTJSDispatch2 *layer = param[0]->AsObjectNoAddRef();
	// x0: arg1 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int x1 = param[1]->AsInteger();
	// y0: arg2 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int y1 = param[2]->AsInteger();
	// x1: arg3 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int x2 = param[3]->AsInteger();
	// y1: arg4 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int y2 = param[4]->AsInteger();
	// color: arg5 = tTVInteger tTJSVariant::AsInteger() const
	tjs_int color = param[5]->AsInteger();

	//get layer stuff
	tTJSVariant bmpobject = tTJSVariant(layer, layer);
	tTJSVariantClosure bmpobject_clo = bmpobject.AsObjectClosureNoAddRef();
	GetBitmapInformationFromObject(bmpobject_clo, true, &dest_width, &dest_height, &dest_pitch, (tjs_uint8 **)&dest_buffer);
	//setting of global variables
	sub_10001260(dest_buffer, dest_pitch, dest_width, dest_height);
	//call sub_100012A0
	if (sub_100011A0(&x1, &y1, &x2, &y2) >= 0)
	{
		sub_100012A0(x1, y1, x2, y2, color);
	}
	//update layer
	UpdateWholeLayerWithLayerObject(bmpobject_clo);

	return TJS_S_OK;
}

#if 0
NCB_REGISTER_FUNCTION(drawAATriangle, drawAATriangle);
#endif
NCB_REGISTER_FUNCTION(drawAALine, drawAALine);
NCB_REGISTER_FUNCTION(drawLine, drawLine);
