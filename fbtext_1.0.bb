DESCRIPTION = "Simple program for writing a new framebuffer to stdout that contains the given input string"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=f98d55b2dbfee628e6c8b0445667d84d"

DEPENDS = "freetype liberation-fonts draw2fb"

inherit pkgconfig

S = "${WORKDIR}"

SRC_URI = " \
	git://github.com/gmalysa/fbtext.git;protocol=https;branch=master \
"

SRCREV = "${AUTOREV}"

do_compile() {
	oe_runmake -C ${S} fbtext
	oe_runmake -C ${S} fbdump
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/fbtext ${D}${bindir}/fbtext
	install -m 0755 ${WORKDIR}/fbdump ${D}${bindir}/fbdump
}

FILES_${PN} = " \
	${bindir}/fbtext \
	${bindir}/fbdump \
"
