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
        self.options["boost"].header_only = True

    def requirements(self):
        self.requires("catch2/2.13.7")
        self.requires("magic_enum/[>=0.9.5 <10]")
        self.requires("boost/1.85.0")
        self.requires("di/1.3.0")
###   for testing types do not put this in the conan recip ####
        self.requires("login_matchmaking_game_shared/latest")
        self.requires("modern_durak_game_shared/latest")
###############################################################

