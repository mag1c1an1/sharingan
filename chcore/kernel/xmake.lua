
add_rules("mode.debug", "mode.release")

target("chcore",function  ()
    set_kind("binary")
    add_files("src/*.c") 
    add_includedirs("include")
    add_includedirs("include/arch/plat/raspi3")
end)
