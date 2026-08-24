{ 
  description = "Development environment for darwiin-org/darwiin-org.github.io";
  
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
   flake-utils.lib.eachSystem [
   "x86_64-linux"
   "x86_64-darwin"
   "x86_64-freebsd"
   ] (system: 
     let 
       pkgs = import nixpkgs { inherit system; };
     in
     {
       devShells.default = pkgs.mkShell {
         nativeBuildInputs = with pkgs; [
          git
          cmake
          gnumake
         ];
         buildInputs = with pkgs; [
          tcl
         ];
         shellHook = ''
           echo "Execute 'make' to build."
           PS1="& "
           PROMPT="& "
         '';
     };
   }
 );
}
