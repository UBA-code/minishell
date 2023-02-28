// cat << $USER - fixed !
// expand herdoc
// en tmp - ?
// export concate
// echo -n duplicates - ?
// sigv when unset first node env - fixed !
// sigv echo kk | << limit - fixed
// set g_global.status in 127 when (path) - already

// execution

here_doc must be set with get_next_line and not readline

// env | grep TMPDIR


if u get empty string in cmd check if there is here_doc or not, if not then this is cmd not found i will print it

//////////////////
/// FAILED TEST // 
//////////////////

`|` : single pipe - done
`>` : abort - done
`<` : abort - done
`>>` : abort + hang - done
`<<` : abort - done
`echo $?` : abort ==> exit code abort on expand function - done
`fjksbf` : no such file >> command not found - done
`cd` : cd home : no such file - done
`CNTL+C` : when execute builtins_utils
`export 1moad=adas` : not a valid indentifier - done
`when unset path and remove parent directory` : go to blackhole - done
`exit asd 2313` : must exit 255 - problem in execution
`exit` : not working - problem in execution
`CTRL+C on heredoc`
`CTRL+D on heredoc`
`echo "|"` : broken
`\t` : skip like space.
<< $"hello" cat
<< $hello cat
env -i ./minishell
`here_doc` : replace gnl w/ readline tabs are normal behavior of bash
