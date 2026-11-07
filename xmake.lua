add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.compile_commands.autoupdate")
add_requires("raylib", "raylib-cpp", "md4c")
if is_plat("wasm") then
    add_requires("emscripten")
end
set_policy("check.auto_ignore_flags", false)
set_policy("build.c++.modules", true)

target("website")
    set_kind("binary")
    set_languages("cxx20")
    add_files("src/*.cxx")

    set_targetdir("$(builddir)/xmake")
    set_objectdir("$(builddir)/xmake/.objs")
    set_dependir("$(builddir)/xmake/.deps")
    set_autogendir("$(builddir)/xmake/.gens")

    if is_plat("wasm") then
        set_targetdir(".")
        set_filename("siteInit.js")
        add_ldflags(
            "-lembind",
            "-flto",
            "-fwasm-exceptions",
            "-sENVIRONMENT=web",
            "-sASSERTIONS=1",
            "--closure 1",
            "--emit-symbol-map",

            -- Required for using Raylib
            "-sUSE_GLFW=3",
            "-sEXPORTED_FUNCTIONS=['_main','_malloc']",
            "-sEXPORTED_RUNTIME_METHODS=ccall"
        )
        add_values("wasm.preloadfiles", "content@/content")
        add_packages("emscripten")
    end
    add_defines("RAYLIB_CXX_INCLUDE=\"raylib-cpp/raylib-cpp.hpp\"")
    add_packages("raylib", "raylib-cpp", "md4c")
    add_includedirs("src")

if is_plat("wasm") then
    on_clean(function (_)
        os.rm("siteInit.*")
    end)
end
