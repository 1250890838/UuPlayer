.pragma library

function convertMillisecondsToDate(ms) {
    const date = new Date(ms)
    const year = date.getFullYear()
    const month = String(date.getMonth() + 1).padStart(2, '0')
    const day = String(date.getDate()).padStart(2, '0')
    return `${year}-${month}-${day}`
}

function millisecondsToTime(ms) {
    let totalSeconds = Math.floor(ms / 1000)
    let minutes = Math.floor(totalSeconds / 60)
    let seconds = totalSeconds % 60
    let formattedTime = `${String(minutes).padStart(2, '0')}:${String(
            seconds).padStart(2, '0')}`
    return formattedTime
}

function formatTime(milliseconds) {
    if (isNaN(milliseconds))
        return "00:00"
    let seconds = Math.floor(milliseconds / 1000)
    let minutes = Math.floor(seconds / 60)
    seconds = seconds % 60
    return Qt.formatTime(new Date(0, 0, 0, 0, minutes, seconds), "mm:ss")
}

function findClosestLowerIndexBinarySearch(arr, targetTime) {
    let left = 0
    let right = arr.length - 1
    let result = -1
    while (left <= right) {
        const mid = Math.floor((left + right) / 2)
        const midTime = arr[mid].end

        if (midTime <= targetTime) {
            result = mid
            left = mid + 1
        } else {
            right = mid - 1
        }
    }
    return result
}
