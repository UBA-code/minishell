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

`CNTL+C` : when execute builtins_utils
`exit asd 2313` : must exit 255 - problem in execution
`exit` : not working - problem in execution
`CTRL+C on heredoc`
`CTRL+D on heredoc`
<< $"hello" cat
<< $hello cat
env -i ./minishell
`here_doc` : replace gnl w/ readline tabs are normal behavior of bash
<< eof 
//////////////////
/// FAILED TEST // 
//////////////////



`cd` (null)

skip blank car o cmd

echo "" hello


ctrl + d not display exit

