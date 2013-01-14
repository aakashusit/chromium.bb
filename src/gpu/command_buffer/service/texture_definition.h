// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_SERVICE_TEXTURE_DEFINITION_H_
#define GPU_COMMAND_BUFFER_SERVICE_TEXTURE_DEFINITION_H_

#include <vector>

#include "base/callback.h"
#include "gpu/command_buffer/service/gl_utils.h"
#include "gpu/gpu_export.h"

namespace gpu {
namespace gles2 {

// A saved definition of a texture that still exists in the underlying
// GLShareGroup and can be used to redefine a client visible texture in any
// context using the same GLShareGroup with the corresponding service ID.
class GPU_EXPORT TextureDefinition {
 public:
  struct LevelInfo {
    LevelInfo(GLenum target,
              GLenum internal_format,
              GLsizei width,
              GLsizei height,
              GLsizei depth,
              GLint border,
              GLenum format,
              GLenum type,
              bool cleared);
    GLenum target;
    GLenum internal_format;
    GLsizei width;
    GLsizei height;
    GLsizei depth;
    GLint border;
    GLenum format;
    GLenum type;
    bool cleared;
  };

  typedef std::vector<std::vector<LevelInfo> > LevelInfos;

  typedef base::Callback<void(TextureDefinition*)> DestroyCallback;

  TextureDefinition(GLenum target,
                    GLuint service_id,
                    bool immutable,
                    const LevelInfos& level_infos);
  ~TextureDefinition();

  GLenum target() const {
    return target_;
  }

  GLuint ReleaseServiceId();

  bool immutable() const { return immutable_; }

  const LevelInfos& level_infos() const {
    return level_infos_;
  }

 private:
  GLenum target_;
  GLuint service_id_;
  bool immutable_;
  std::vector<std::vector<LevelInfo> > level_infos_;

  DISALLOW_COPY_AND_ASSIGN(TextureDefinition);
};

}  // namespage gles2
}  // namespace gpu

#endif  // GPU_COMMAND_BUFFER_SERVICE_TEXTURE_DEFINITION_H_