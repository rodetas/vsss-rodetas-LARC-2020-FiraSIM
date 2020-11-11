team = ""
    while getopts "h?tc:" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    t)  verbose=1
        ;;
    c)  team=$OPTARG
        ;;
    esac
done
    sudo ./SDK-Rodetas -c team
