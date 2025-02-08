.pragma library

function convertMillisecondsToDate(ms) {
    const date = new Date(ms)
    // Convert milliseconds to Date object

    // Get the components of the date
    const year = date.getFullYear()
    const month = String(date.getMonth() + 1).padStart(2, '0')
    // Months are zero-based, so add 1
    const day = String(date.getDate()).padStart(2, '0')
    // Ensure day is two digits

    // Return the formatted date
    return `${year}-${month}-${day}`
}

function millisecondsToTime(ms) {
    // Get total seconds
    let totalSeconds = Math.floor(ms / 1000)

    // Get minutes and seconds
    let minutes = Math.floor(totalSeconds / 60)
    let seconds = totalSeconds % 60

    // Format minutes and seconds to always show two digits
    let formattedTime = `${String(minutes).padStart(2, '0')}:${String(
            seconds).padStart(2, '0')}`

    return formattedTime
}
