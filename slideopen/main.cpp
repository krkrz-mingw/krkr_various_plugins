
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ncbind.hpp"
#include "layer_util.h"

static struct
{
	tjs_int src_width, src_height, src_pitch;
	tjs_uint8 *src_buffer;
	tjs_int dest_width, dest_height, dest_pitch;
	tjs_uint8 *dest_buffer;
	iTJSDispatch2 *dest_dispatch;
	bool open;
	tjs_int type;
	tjs_int current_type;
	tjs_uint8 *buffer;
	tjs_uint8 *buffer_aligned;
	tjs_int pitch;
} slideopen_args;

static int sub_10001000(int a1, int dest_width, int dest_height)
{
	tjs_uint32* v3;
	int result;
	tjs_uint32* v5;
	int v6;
	int v8;
	tjs_uint32 *v9;
	int v11;
	tjs_uint32 *v12;
	int v13;
	int v14;
	int v17;
	int v19;
	tjs_uint32 *v20;
	int v21;
	int v22;
	int v24;
	tjs_uint32* v26;
	int v28;
	tjs_uint32 v29;
	int v31;
	int v32;

	v26 = (tjs_uint32 *)slideopen_args.src_buffer;
	v29 = (tjs_uint32)slideopen_args.dest_pitch >> 2;
	v3 = (tjs_uint32 *)slideopen_args.buffer_aligned;
	result = dest_width / 2;
	v5 = (tjs_uint32 *)slideopen_args.dest_buffer;
	v28 = dest_width / 2;
	if ( slideopen_args.open )
	{
		if ( dest_height > 0 )
		{
			result -= a1;
			v31 = result;
			for (int i = 0; i < dest_height; i += 1)
			{
				v9 = v3 + a1;
				v6 = result;
				for (int j = 0; j < result; j += 1)
				{
					v5[j] = v9[j];
				}
				int res = result;
				result = v31;
				v12 = v5 + v6;
				v6 = v28 + a1;
#if 1
				for (int j = 0; j < (v28 + a1 - v6); j += 1)
				{
					v12[j] = v26[j + res];
				}
#endif
				result = v31;
				v13 = v6;
				for (int j = 0; j < (dest_width - v6); j += 1)
				{
					v5[j] = v3[-a1];
				}
				v3 += v29;
				v5 += v29;
				v26 += v29;
			}
		}
	}
	else if ( dest_height > 0 )
	{
		result = a1;
		v17 = dest_width / 2 - a1;
		v32 = v17;
		for (int i = 0; i < dest_height; i += 1)
		{
			v20 = (tjs_uint32 *)(v26 + result);
			for (int j = 0; j < v17; j += 1)
			{
				v5[j] = v20[j];
			}
			v22 = v28 + result;
			if ( v22 < dest_width )
			{
#if 1
				for (int j = 0; j < (dest_width - v22); j += 1)
				{
					v5[j] = v26[v28 + j];
				}
#endif
				v17 = v32;
			}
			v5 += v29;
			v26 += v29;
		}
	}
	return result;
}

static int sub_100011B0(int a1, int dest_width, int dest_height)
{
	tjs_uint32* v3;
	int v4;
	int v5;
	tjs_uint32 v6;
	int v7;
	int v10;
	int v11;
	tjs_uint32* v12;
	int v13;
	tjs_uint32* v16;
	int result;
	int v21;
	int v22;
	tjs_uint32* v23;
	tjs_uint32* v26;
	tjs_uint32* v27;
	tjs_uint32 v31;
	tjs_uint32* v32;
	int v33;
	int v37;
	int v38;

	v3 = (tjs_uint32 *)slideopen_args.dest_buffer;
	v4 = a1;
	v5 = dest_height / 2;
	v6 = (tjs_uint32)slideopen_args.dest_pitch >> 2;
	v31 = (tjs_uint32)slideopen_args.dest_pitch >> 2;
	v33 = dest_height / 2;
	if ( a1 > dest_height / 2 )
	{
		v4 = dest_height / 2;
		a1 = dest_height / 2;
	}
	if ( slideopen_args.open )
	{
		v37 = 0;
		v7 = v5 - v4;
		v32 = (tjs_uint32*)slideopen_args.buffer_aligned + v4 * v6;
		if ( v5 - v4 <= 0 )
		{
		}
		else
		{
			v37 = v5 - v4;
			for (int i = 0; i < (v5 - v4); i += 1)
			{
				for (int j = 0; j < dest_width; j += 1)
				{
					v3[j] = v32[j];
				}
				v6 = v31;
				v3 += v6;
				v32 += v6;
			}
			v5 = dest_height / 2;
		}
		v10 = v4 + v5;
		v11 = v37;
		v12 = (tjs_uint32*)slideopen_args.src_buffer + v6 * v7;
		if ( v37 < v10 )
		{
			v13 = v10 - v37;
			v11 = v13 + v37;
			v38 = v13 + v37;
			for (int i = 0; i < v13; i += 1)
			{
				for (int j = 0; j < dest_width; j += 1)
				{
					v3[j] = v12[j];
				}
				v6 = v31;
				v11 = v38;
				v12 += v6;
				v3 += v6;
			}
		}
		v16 = (tjs_uint32*)slideopen_args.buffer_aligned + v6 * v33;
		result = dest_height;
		if ( v11 < dest_height )
		{
			for (int i = 0; i < dest_height - v11; i += 1)
			{
				if ( dest_width > 0 )
				{
					for (int j = 0; j < dest_width; j += 1)
					{
						v3[j] = v16[j];
					}
					v6 = v31;
				}
				result = v6;
				v16 += v6;
				v3 += v6;
			}
		}
	}
	else
	{
		v21 = v4 * v6;
		v22 = v5 - v4;
		v23 = (tjs_uint32*)slideopen_args.src_buffer + v4 * v6;
		if ( v22 > 0 )
		{
			for (int i = 0; i < v22; i += 1)
			{
				if ( dest_width > 0 )
				{
					for (int j = 0; j < dest_width; j += 1)
					{
						v3[j] = v23[j];
					}
					v4 = a1;
					v6 = v31;
				}
				v23 += v6;
				v3 += v6;
			}
		}
		v26 = v3 + 2 * v21;
		result = v4 + v33;
		v27 = (tjs_uint32*)slideopen_args.src_buffer + v6 * v33;
		if ( v4 + v33 < dest_height )
		{
			for (int i = 0; i < (dest_height - result); i += 1)
			{
				for (int j = 0; j < dest_width; j += 1)
				{
					v26[j] = v27[j];
				}
				v6 = v31;
				result = v6;
				v27 += v6;
				v26 += v6;
			}
		}
	}
	return result;
}

static int sub_100013D0(int a1, int dest_width, int dest_height)
{
	int v4;
	int result;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
	int v12;
	int v14;
	int v16;
	int v17;
	tjs_uint32 *v18;
	tjs_uint32* v19;
	int v21;
	int v23;
	int v24;
	tjs_uint32* v26;
	tjs_uint32* v28;
	tjs_uint32* v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;
	tjs_uint32* v35;
	int v38;

	v26 = (tjs_uint32 *)slideopen_args.dest_buffer;
	v35 = (tjs_uint32 *)slideopen_args.src_buffer;
	v24 = slideopen_args.dest_pitch / 4;
	v4 = dest_height / 2;
	v31 = dest_width / 2;
	v34 = dest_height / 2;
	v30 = dest_width / 2 + dest_height / 2 - a1;
	result = a1 / -2;
	v6 = a1 / 2;
	v38 = a1 / -2 + a1;
	v7 = a1 - a1 / 2;
	if ( !slideopen_args.open )
		return result;
	v29 = (tjs_uint32*)slideopen_args.buffer_aligned + (v7 + v24 * v6);
	v8 = v24 * result;
	v28 = (tjs_uint32*)slideopen_args.buffer_aligned + (v31 + v4 + v24 * result + v38);
	if ( v6 >= 0 )
	{
		if ( v6 < dest_height )
			goto LABEL_7;
		v6 -= dest_height;
	}
	else
	{
		v6 += dest_height;
	}
	v9 = v7 + v24 * v6;
	v29 = (tjs_uint32*)slideopen_args.buffer_aligned + v9;
LABEL_7:
	if ( result >= 0 )
	{
		v10 = a1 / -2 + a1;
		if ( result < dest_height )
			goto LABEL_12;
		v10 = dest_height + v38;
		result -= dest_height;
		v38 += dest_height;
	}
	else
	{
		v10 = v38 - dest_height;
		result += dest_height;
		v38 -= dest_height;
	}
	v8 = v24 * result;
	v28 = (tjs_uint32*)slideopen_args.buffer_aligned + (v31 + v34 + v24 * result + v10);
LABEL_12:
	if ( dest_height > 0 )
	{
		v33 = v8;
		v32 = dest_height * v24;
		for (int i = 0; i < dest_height; i += 1)
		{
			v11 = v30;
			v12 = v30;
			for (int j = 0; j < v30; j += 1)
			{
				v26[j] = v29[j];
			}
			v11 = v30;
			v14 = v11 + 2 * a1;
			if ( v14 > dest_width )
				v14 = dest_width;
			if ( v12 < v14 )
			{
				v16 = (tjs_uint8 *)v35 - (tjs_uint8 *)v26;
				v17 = v14 - v12;
				v18 = (tjs_uint32 *)((tjs_uint8 *)v26 + v12);
				v12 += v17;
#if 1
				for (int j = 0; j < (v14 - v12); j += 1)
				{
					v18[j] = *(tjs_uint32 *)((tjs_uint8 *)&v18[j] + v16);
					v16 = (tjs_uint8 *)v35 - (tjs_uint8 *)v26;
				}
#endif
				v10 = v38;
			}
			if ( v12 < dest_width )
			{
				v19 = v26 + v12;
				for (int j = 0; j < (dest_width - v12); j += 1)
				{
					v19[j] = v28[j];
				}
			}
			v30 -= 1;
			v26 += v24;
			v6 += 1;
			v10 -= 1;
			v29 += v24;
			result += 1;
			v38 = v10;
			v28 += v24 - 4;
			v21 = v24 + v33;
			v33 += v24;
			v35 += v24;
			if ( v6 >= 0 )
			{
				if ( v6 < dest_height )
					goto LABEL_33;
				v6 -= dest_height;
				v29 -= v32;
			}
			else
			{
				v6 += dest_height;
				v29 += v32;
			}
LABEL_33:
			if ( result < 0 )
			{
				v10 -= dest_height;
				result += dest_height;
				v38 = v10;
				v23 = v32 + v21;
LABEL_37:
				v33 = v23;
				v28 = (tjs_uint32*)slideopen_args.buffer_aligned + (v31 + v34 + v10 + v23);
				goto LABEL_38;
			}
			if ( result >= dest_height )
			{
				v10 += dest_height;
				result -= dest_height;
				v38 = v10;
				v23 = v21 - v32;
				goto LABEL_37;
			}
		}
	}
LABEL_38:
	return result;
}

static int sub_100016C0(int a1, int dest_width, int dest_height)
{
	int v4;
	int v5;
	tjs_uint32 v6;
	int result;
	int v8;
	int v9;
	int v11;
	int v13;
	tjs_uint32* v15;
	int v16;
	int v17;
	tjs_uint32* v19;
	int v20;
	int v21;
	int v23;
	tjs_uint32* v24;
	tjs_uint32 v25;
	tjs_uint32* v26;
	tjs_uint32* v27;
	tjs_uint32* v28;
	int v29;
	int v30;
	int v31;
	int v32;
	int v33;
	int v34;
	int v35;
	int v36;
	int v37;
	tjs_uint32 *v38;
	tjs_uint32* v39;
	int v40;

	v27 = (tjs_uint32*)slideopen_args.dest_buffer;
	v39 = (tjs_uint32*)slideopen_args.src_buffer;
	v24 = (tjs_uint32*)slideopen_args.buffer_aligned;
	v4 = dest_height / 2;
	v30 = dest_width / 2;
	v34 = dest_height / 2;
	v29 = dest_width / 2 - dest_height / 2 - a1;
	v5 = a1 / -2;
	v6 = (tjs_uint32)slideopen_args.dest_pitch >> 2;
	v25 = (tjs_uint32)slideopen_args.dest_pitch >> 2;
	v32 = a1 / -2 + a1;
	result = a1 / 2;
	v8 = a1 - a1 / 2;
	if ( !slideopen_args.open )
		return result;
	v28 = (tjs_uint32*)slideopen_args.buffer_aligned + (v32 + v6 * v5);
	v9 = v25 * result;
	v26 = (tjs_uint32*)slideopen_args.buffer_aligned + (v30 + v8 + v25 * result - v4);
	if ( v5 >= 0 )
	{
		if ( v5 < dest_height )
			goto LABEL_7;
		v5 -= dest_height;
	}
	else
	{
		v5 += dest_height;
	}
	v28 = (tjs_uint32*)slideopen_args.buffer_aligned + (v32 + v25 * v5);
LABEL_7:
	if ( result >= 0 )
	{
		if ( result < dest_height )
			goto LABEL_12;
		v8 -= dest_height;
		result -= dest_height;
	}
	else
	{
		v8 += dest_height;
		result += dest_height;
	}
	v9 = v25 * result;
	v26 = (tjs_uint32*)slideopen_args.buffer_aligned + (v30 + v8 + v25 * result - v34);
LABEL_12:
	if ( dest_height > 0 )
	{
		v33 = v9;
		v31 = dest_height * v25;
		for (int i = 0; i < dest_height; i += 1)
		{
			v11 = v29;
			for (int j = 0; j < v29; j += 1)
			{
				v27[j] = v28[j];
			}
			v13 = v29 + 2 * a1;
			v36 = v13;
			if ( v13 > dest_width )
			{
				v13 = dest_width;
				v36 = dest_width;
			}
			if ( v11 < v13 )
			{
				v15 = v27 + v11;
				v16 = (tjs_uint8 *)v39 - (tjs_uint8 *)v27;
				v17 = v36 - v11;
				v11 += v17;
				for (int j = 0; j < v17; j += 1)
				{
					v15[j] = *(tjs_uint32 *)((tjs_uint8 *)v15 + v16);
					v16 = (tjs_uint8 *)v39 - (tjs_uint8 *)v27;
				}
			}
			if ( v11 < dest_width )
			{
				v19 = v27 + v11;
				v38 = v26;
				for (int j = 0; j < (dest_width - v11); j += 1)
				{
					v19[j] = v38[j];
				}
			}
			v29 += 1;
			v27 += v25;
			v5 += 1;
			v8 += 1;
			v28 += v25;
			result += 1;
			v26 += v25 + 4;
			v21 = v25 + v33;
			v33 += v25;
			v39 += v25;
			if ( v5 >= 0 )
			{
				if ( v5 < dest_height )
					goto LABEL_33;
				v5 -= dest_height;
				v28 -= v31;
			}
			else
			{
				v5 += dest_height;
				v28 += v31;
			}
LABEL_33:
			if ( result < 0 )
			{
				v8 += dest_height;
				result += dest_height;
				v23 = v31 + v21;
LABEL_37:
				v33 = v23;
				v26 = v24 + (v30 + v8 + v23 - v34);
				goto LABEL_38;
			}
			if ( result >= dest_height )
			{
				v8 -= dest_height;
				result -= dest_height;
				v23 = v21 - v31;
				goto LABEL_37;
			}
		}
	}
LABEL_38:
	return result;
}


static tjs_error TJS_INTF_METHOD
finishSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A0E0 10002330
	if (slideopen_args.buffer)
	{
		free(slideopen_args.buffer);
		slideopen_args.buffer = NULL;
	}
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
drawSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A15C 100020d0
	if (!numparams) return TJS_E_BADPARAMCOUNT;
	//arg1 = tTVReal tTJSVariant::AsReal() const
	tjs_real a1 = param[0]->AsReal();
	if (!slideopen_args.open)
	{
		a1 = 1.0 - a1;
	}
	tjs_real a2 = (tjs_real)(slideopen_args.dest_width / 2) * a1 + 0.5;
	tjs_int a3 = (tjs_int64)a2;
	switch (slideopen_args.type)
	{
		case 0:
			sub_10001000(a3, slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		case 1:
			sub_100011B0(a3, slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		case 2:
			sub_100013D0((tjs_int64)((tjs_real)a3 * 1.75), slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		case 3:
			sub_100016C0((tjs_int64)((tjs_real)a3 * 1.75), slideopen_args.dest_width, slideopen_args.dest_height);
			break;
		default:
			break;
	}
	update_layer(slideopen_args.dest_dispatch, 0, 0, slideopen_args.dest_width, slideopen_args.dest_height);
	return TJS_S_OK;
}

static tjs_error TJS_INTF_METHOD
initSlideOpen(tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis) {
	// TODO: Stub 1000A1D8 10001c70
	if (!numparams) return TJS_E_BADPARAMCOUNT;

	//arg0 = Slide Open plugin object/dictionary
	ncbPropAccessor dict(param[0]->AsObjectNoAddRef());
	// open: tTJSVariant::operator tjs_int() const
	slideopen_args.open = dict.getIntValue(TJS_W("open"), 1);
	// dest: layer pointer
	tTJSVariant dest;
	if (dict.checkVariant(TJS_W("dest"), dest))
	{
		get_layer_pointers(dest, &slideopen_args.dest_buffer, &slideopen_args.dest_width, &slideopen_args.dest_height, &slideopen_args.dest_pitch);
		slideopen_args.dest_dispatch = dest.AsObject();
	}
	else
	{
		return TJS_E_FAIL;
	}
	// src: layer pointer
	tTJSVariant src;
	if (dict.checkVariant(TJS_W("src"), src))
	{
		get_layer_pointers(src, &slideopen_args.src_buffer, &slideopen_args.src_width, &slideopen_args.src_height, &slideopen_args.src_pitch);
	}
	else
	{
		return TJS_E_FAIL;
	}
	// type: tTJSVariant::operator tjs_int() const
	tTJSVariant type_var;
	if (dict.checkVariant(TJS_W("type"), type_var))
	{
		slideopen_args.type = dict.getIntValue(TJS_W("type"));
	}

	if (slideopen_args.src_width != slideopen_args.dest_width || slideopen_args.src_height != slideopen_args.dest_height || slideopen_args.src_pitch != slideopen_args.dest_pitch)
	{
		return TJS_E_FAIL;
	}
	if (slideopen_args.open)
	{
		slideopen_args.buffer = malloc(4 * slideopen_args.dest_height * slideopen_args.dest_width + 4);
		slideopen_args.buffer_aligned = (tjs_uint8*)((tjs_uint8 *)slideopen_args.buffer - ((size_t)slideopen_args.buffer & 3) + 4);
		if (slideopen_args.dest_pitch < 1)
		{
			slideopen_args.buffer_aligned -= slideopen_args.dest_pitch * (slideopen_args.dest_height - 1);
		}
		tjs_uint8 *v21 = slideopen_args.dest_buffer;
		tjs_uint32 *v22 = (tjs_uint32 *)(slideopen_args.buffer_aligned);
		tjs_uint32 v33 = (tjs_uint32)slideopen_args.dest_pitch >> 2;
		for (tjs_int i = 0; i < slideopen_args.dest_height; i += 1)
		{
			tjs_uint32* v25 = v22;
			for (tjs_int j = 0; j < slideopen_args.dest_width; j += 1)
			{
				*v25 = *(tjs_uint32 *)(v25 - v22 + v21);
				++v25;
			}
			v22 += v33;
			v21 += 4 * v33;
		}
	}
	if ( slideopen_args.type < 0 )
	{
		slideopen_args.type = TVPGetTickCount() & 3;
		if ( slideopen_args.current_type != slideopen_args.type )
			goto LABEL_52;
		slideopen_args.type += 1;
	}
	slideopen_args.type &= 3u;
LABEL_52:
	if ( !slideopen_args.open )
	{
		slideopen_args.type &= 1u;
	}
	slideopen_args.current_type = slideopen_args.type;
	return TJS_S_OK;
}

NCB_REGISTER_FUNCTION(finishSlideOpen, finishSlideOpen);
NCB_REGISTER_FUNCTION(drawSlideOpen, drawSlideOpen);
NCB_REGISTER_FUNCTION(initSlideOpen, initSlideOpen);
