{
  description = "trapped knight revisited revisited";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils = {
      inputs.nixpkgs.follows = "nixpkgs";
      url = "github:numtide/flake-utils";
    };
  };

  outputs = { self, nixpkgs, flake-utils, ... }@inputs:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
        rec {
          defaultApp = apps.trappedknight;
          defaultPackage = packages.trappedknight;

          apps.trappedknight = {
            type = "app";
            program = "${defaultPackage}/bin/trappedknight";
          };
          packages.trappedknight = pkgs.stdenv.mkDerivation {
            name = "trappedknight";
            pname = "trappedknight";
            version = "1.0";
            src = ./src;
          
            buildInputs = with pkgs; [
              # dependencies
            ];
            makeFlags = [
              "DESTDIR=$(out)"
            ];
            # buildPhase = ''
            #   cp $src/bin/lal $out/bin/lal
            # '';
            # installPhase = ''
            #   cp $src/bin/lal $out/bin/lal
            # '';
          };
        }
      );
}
