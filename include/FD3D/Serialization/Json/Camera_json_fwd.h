#ifndef FD3D_CAMERA_JSON_FWD_H
#define FD3D_CAMERA_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FD3D/Camera/Camera.h>

namespace FDJson
{
    rapidjson::Value serialize(const FD3D::Camera &cam, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FD3D::Camera &cam, Serializer &serializer, std::string *err = nullptr);
}

#endif // FD3D_CAMERA_JSON_FWD_H
