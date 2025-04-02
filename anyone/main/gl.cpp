void check_gl_version()
{
    auto gl_version = glGetString(GL_VERSION);
    LOG("OpenGL version: %s", gl_version);
    int major, minor;
    if (sscanf((const char*)gl_version, "%d.%d", &major, &minor) != 2) {
        NX_PANIC("parse gl_version error");
    }

    if (major == 3 || minor >= 3) {
    } else if (major >= 4) {
    } else {
        NX_PANIC("gl_version is too low");
    }
}

void set_global_gl_state()
{
    glDisable(GL_MULTISAMPLE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_BLEND);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
}

} // namespace anyone