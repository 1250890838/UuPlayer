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
