# Build for variableCount()

Dependency on libxml2, the libxml2 library and multiple libxml2 include files.

## macOS

The libxml2 library is installed by default. Matching include files require the installation of Xcode, and/or Xcode command-line tools:

```
xcode-select --install
```

### macOS Mojave:

* Must create /usr/include files:

```
open /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg
```
