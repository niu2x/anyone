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
