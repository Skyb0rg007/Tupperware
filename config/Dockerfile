FROM centos/devtoolset-7-toolchain-centos7

USER 0
RUN yum install -y --setopt=tsflags=nodocs \
    devtoolset-7-make \
    devtoolset-7-llvm \
    devtoolset-7-valgrind \
    rh-python36

RUN yum clean all -y
USER 1000

# devtoolset-7 llvm-toolset-7 rh-python36
