from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class Project(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators =  "CMakeDeps"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False #workaround because this leads to useless options in cmake-tools configure
        tc.generate()

    def configure(self):
        self.options["catch2"].with_main = True
        self.options["catch2"].with_benchmark = True

    def requirements(self):
        self.requires("catch2/3.9.0")
        self.requires("magic_enum/0.9.6")
        self.requires("boost/1.86.0")

        # only for tests
        self.requires("durak/1.1.1")
        ################
