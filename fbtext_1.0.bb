DESCRIPTION = "Simple program for writing a new framebuffer to stdout that contains the given input string"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=f17cf300a93d4fa3f9f0cd408949ade3"

DEPENDS = "freetype liberation-fonts draw2fb"

inherit pkgconfig

S = "${WORKDIR}/git"

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
	install -m 0755 ${S}/fbtext ${D}${bindir}/fbtext
	install -m 0755 ${S}/fbdump ${D}${bindir}/fbdump
}

FILES_${PN} = " \
	${bindir}/fbtext \
	${bindir}/fbdump \
"
