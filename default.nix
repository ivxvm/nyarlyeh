with import <nixpkgs> {};

stdenv.mkDerivation {
  name = "nyarlyeh-0.1";
  src = ./.;
  installPhase = ''
    ./nyarlyeh
  '';
  # installPhase = ''
  #   mkdir -p $out/lib
  #   mkdir -p $out/include

  #   # the buildPhase has already produced libfoo.a
  #   cp libfoo.a $out/lib
  #   cp foo.h    $out/include
  # '';
}
