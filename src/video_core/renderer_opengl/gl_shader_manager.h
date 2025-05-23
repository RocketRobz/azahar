// Copyright Citra Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include "video_core/rasterizer_interface.h"

namespace Frontend {
class EmuWindow;
}

namespace Pica {
struct RegsInternal;
struct ShaderSetup;
} // namespace Pica

namespace Pica::Shader {
union UserConfig;
}

namespace OpenGL {

class Driver;
class OpenGLState;

enum UniformBindings {
    VSPicaData = 0,
    VSData = 1,
    FSData = 2,
};

/// A class that manage different shader stages and configures them with given config data.
class ShaderProgramManager {
public:
    ShaderProgramManager(Frontend::EmuWindow& emu_window, const Driver& driver, u64 title_id,
                         bool separable);
    ~ShaderProgramManager();

    void LoadDiskCache(const std::atomic_bool& stop_loading,
                       const VideoCore::DiskResourceLoadCallback& callback, bool accurate_mul);

    bool UseProgrammableVertexShader(const Pica::RegsInternal& config, Pica::ShaderSetup& setup,
                                     bool accurate_mul);

    void UseTrivialVertexShader();

    void UseFixedGeometryShader(const Pica::RegsInternal& regs);

    void UseTrivialGeometryShader();

    void UseFragmentShader(const Pica::RegsInternal& config, const Pica::Shader::UserConfig& user);

    void ApplyTo(OpenGLState& state, bool accurate_mul);

    u64 GetProgramID() const;

private:
    Frontend::EmuWindow& emu_window;
    const Driver& driver;
    bool strict_context_required;
    class Impl;
    std::unique_ptr<Impl> impl;
};
} // namespace OpenGL
