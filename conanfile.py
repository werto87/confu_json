from conan import ConanFile


class Project(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"


    def requirements(self):
        self.requires("catch2/2.13.7")
        self.requires("magic_enum/[>=0.9.5 <10]")
        self.requires("boost/1.83.0")



