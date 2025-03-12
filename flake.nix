{
  description = "A Nix-flake-based C/C++ development environment";

  inputs.nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/0.1.*.tar.gz";

  outputs = {
    self,
    nixpkgs,
  }: let
    supportedSystems = ["x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin"];
    forEachSupportedSystem = f:
      nixpkgs.lib.genAttrs supportedSystems (system:
        f {
          pkgs = import nixpkgs {inherit system;};
        });
  in {
    devShells = forEachSupportedSystem ({pkgs}: {
      default = let
        pico-sdk = pkgs.pico-sdk.override {withSubmodules = true;};
      in
        pkgs.mkShell.override
        {
          # Override stdenv in order to change compiler:
          # stdenv = pkgs.clangStdenv;
        }
        {
          PICO_SDK_PATH = "${pico-sdk}/lib/pico-sdk";
          packages = [
            pico-sdk
            pkgs.gcc-arm-embedded
            pkgs.python3
          ];
        };
    });
  };
}
