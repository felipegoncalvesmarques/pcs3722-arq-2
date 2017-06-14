FROM ubuntu:16.04
MAINTAINER Felipe Gonçalves Marques

# Packages
RUN apt-get update && \
    apt-get install --no-install-recommends -y binutils locales \
    gcc make build-essential \
    && rm -rf /var/lib/apt/lists/*

# Environment
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8

# Non-root "student" user
RUN useradd -mG sudo student && mkdir -p /etc/sudoers.d && \
    echo '%sudo   ALL=(ALL:ALL) NOPASSWD: ALL' > /etc/sudoers.d/sudo_nopasswd && \
    mkdir -p /home/student

COPY ./entrypoint.sh /
COPY ./default_cmd.sh /
ENTRYPOINT ["/entrypoint.sh"]
CMD ["/default_cmd.sh"]
