
add_rules("mode.debug", "mode.release")

target("chcore",function () 
    set_kind("binary")
    add_files("src/*.c") 
    add_includedirs("include")
end)
