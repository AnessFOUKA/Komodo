FROM ubuntu:24.04
ENV VITASDK=/usr/dev/vitasdk/
ENV PATH=${VITASDK}/bin:${PATH}
COPY ./vitasdk_install.sh /KomodoV2/toolchain/
RUN cd /KomodoV2/toolchain/ && chmod +x ./vitasdk_install.sh && ./vitasdk_install.sh