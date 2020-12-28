cmake_minimum_required(VERSION 3.10)

project(LocalizedProg)

add_custom_target(allclean COMMAND rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile LocalizedProg ru prog.new.pot)

add_custom_target(
    new.pot
    ALL
    DEPENDS prog.c prog.pot
    COMMAND xgettext -k_ prog.c -o prog.new.pot
    COMMAND msgmerge -U prog.pot prog.new.pot
)
add_custom_target(
    ru.po
    ALL
    DEPENDS prog.pot prog.c
    COMMAND msgmerge -U ru.po prog.pot
)
add_custom_target(
    prog.mo
    ALL
    DEPENDS ru.po
    COMMAND mkdir -p ru/LC_MESSAGES/
    COMMAND msgfmt ru.po -o ru/LC_MESSAGES/prog.mo
)

add_executable(LocalizedProg prog.c)

