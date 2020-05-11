#pragma once
#include "base/ccConfig.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

extern se::Object* __jsb_cocos2d_FileUtils_proto;
extern se::Class* __jsb_cocos2d_FileUtils_class;

bool js_register_cocos2d_FileUtils(se::Object* obj);
bool register_all_engine(se::Object* obj);
SE_DECLARE_FUNC(js_engine_FileUtils_writeDataToFile);
SE_DECLARE_FUNC(js_engine_FileUtils_fullPathForFilename);
SE_DECLARE_FUNC(js_engine_FileUtils_getStringFromFile);
SE_DECLARE_FUNC(js_engine_FileUtils_removeFile);
SE_DECLARE_FUNC(js_engine_FileUtils_getDataFromFile);
SE_DECLARE_FUNC(js_engine_FileUtils_isAbsolutePath);
SE_DECLARE_FUNC(js_engine_FileUtils_renameFile);
SE_DECLARE_FUNC(js_engine_FileUtils_normalizePath);
SE_DECLARE_FUNC(js_engine_FileUtils_getDefaultResourceRootPath);
SE_DECLARE_FUNC(js_engine_FileUtils_loadFilenameLookupDictionaryFromFile);
SE_DECLARE_FUNC(js_engine_FileUtils_isPopupNotify);
SE_DECLARE_FUNC(js_engine_FileUtils_getValueVectorFromFile);
SE_DECLARE_FUNC(js_engine_FileUtils_getSearchPaths);
SE_DECLARE_FUNC(js_engine_FileUtils_getFileDir);
SE_DECLARE_FUNC(js_engine_FileUtils_writeToFile);
SE_DECLARE_FUNC(js_engine_FileUtils_getOriginalSearchPaths);
SE_DECLARE_FUNC(js_engine_FileUtils_listFiles);
SE_DECLARE_FUNC(js_engine_FileUtils_getValueMapFromFile);
SE_DECLARE_FUNC(js_engine_FileUtils_getFileSize);
SE_DECLARE_FUNC(js_engine_FileUtils_getValueMapFromData);
SE_DECLARE_FUNC(js_engine_FileUtils_removeDirectory);
SE_DECLARE_FUNC(js_engine_FileUtils_setSearchPaths);
SE_DECLARE_FUNC(js_engine_FileUtils_writeStringToFile);
SE_DECLARE_FUNC(js_engine_FileUtils_setSearchResolutionsOrder);
SE_DECLARE_FUNC(js_engine_FileUtils_addSearchResolutionsOrder);
SE_DECLARE_FUNC(js_engine_FileUtils_addSearchPath);
SE_DECLARE_FUNC(js_engine_FileUtils_writeValueVectorToFile);
SE_DECLARE_FUNC(js_engine_FileUtils_isFileExist);
SE_DECLARE_FUNC(js_engine_FileUtils_purgeCachedEntries);
SE_DECLARE_FUNC(js_engine_FileUtils_fullPathFromRelativeFile);
SE_DECLARE_FUNC(js_engine_FileUtils_getSuitableFOpen);
SE_DECLARE_FUNC(js_engine_FileUtils_writeValueMapToFile);
SE_DECLARE_FUNC(js_engine_FileUtils_getFileExtension);
SE_DECLARE_FUNC(js_engine_FileUtils_setWritablePath);
SE_DECLARE_FUNC(js_engine_FileUtils_setPopupNotify);
SE_DECLARE_FUNC(js_engine_FileUtils_isDirectoryExist);
SE_DECLARE_FUNC(js_engine_FileUtils_setDefaultResourceRootPath);
SE_DECLARE_FUNC(js_engine_FileUtils_getSearchResolutionsOrder);
SE_DECLARE_FUNC(js_engine_FileUtils_createDirectory);
SE_DECLARE_FUNC(js_engine_FileUtils_listFilesRecursively);
SE_DECLARE_FUNC(js_engine_FileUtils_getWritablePath);
SE_DECLARE_FUNC(js_engine_FileUtils_setDelegate);
SE_DECLARE_FUNC(js_engine_FileUtils_getInstance);

extern se::Object* __jsb_cocos2d_Device_proto;
extern se::Class* __jsb_cocos2d_Device_class;

bool js_register_cocos2d_Device(se::Object* obj);
bool register_all_engine(se::Object* obj);
SE_DECLARE_FUNC(js_engine_Device_getNetworkType);
SE_DECLARE_FUNC(js_engine_Device_setAccelerometerEnabled);
SE_DECLARE_FUNC(js_engine_Device_setAccelerometerInterval);
SE_DECLARE_FUNC(js_engine_Device_vibrate);
SE_DECLARE_FUNC(js_engine_Device_setKeepScreenOn);
SE_DECLARE_FUNC(js_engine_Device_getBatteryLevel);
SE_DECLARE_FUNC(js_engine_Device_getDeviceRotation);
SE_DECLARE_FUNC(js_engine_Device_getDPI);
SE_DECLARE_FUNC(js_engine_Device_getSafeAreaEdge);
SE_DECLARE_FUNC(js_engine_Device_getDeviceModel);

extern se::Object* __jsb_cocos2d_SAXParser_proto;
extern se::Class* __jsb_cocos2d_SAXParser_class;

bool js_register_cocos2d_SAXParser(se::Object* obj);
bool register_all_engine(se::Object* obj);
SE_DECLARE_FUNC(js_engine_SAXParser_init);

extern se::Object* __jsb_cocos2d_CanvasGradient_proto;
extern se::Class* __jsb_cocos2d_CanvasGradient_class;

bool js_register_cocos2d_CanvasGradient(se::Object* obj);
bool register_all_engine(se::Object* obj);
SE_DECLARE_FUNC(js_engine_CanvasGradient_addColorStop);
SE_DECLARE_FUNC(js_engine_CanvasGradient_CanvasGradient);

extern se::Object* __jsb_cocos2d_CanvasRenderingContext2D_proto;
extern se::Class* __jsb_cocos2d_CanvasRenderingContext2D_class;

bool js_register_cocos2d_CanvasRenderingContext2D(se::Object* obj);
bool register_all_engine(se::Object* obj);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_restore);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_moveTo);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_lineTo);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_setTransform);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_stroke);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_measureText);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_fill);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D__fillImageData);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_scale);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_clearRect);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_transform);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_fillText);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_strokeText);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_save);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_fillRect);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_rotate);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_beginPath);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_rect);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_translate);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_createLinearGradient);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_closePath);
SE_DECLARE_FUNC(js_engine_CanvasRenderingContext2D_CanvasRenderingContext2D);

