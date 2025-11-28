FROM fedora:latest
LABEL Description="Fedora C++ development container."

RUN dnf group install -y development-tools && dnf install -y clang cmake gdb wget && dnf clean all