<?php
/**
 * @file line chart template file
 */
?>

<script type="text/javascript">

google.load("visualization", "1", {packages:["corechart"]});
google.setOnLoadCallback(drawChart);
function drawChart() {
    var data = google.visualization.arrayToDataTable(<?php print $data->getJSArray()?>);

    var options = <?php print $options->getJSON()?>;
    var chart = new google.visualization.LineChart(document.getElementById("<?php print $chart['#chart_id']?>"));
    chart.draw(data, options);
}
</script>

<div class="google-column-chart">
  <div id="<?php print $chart['#chart_id']?>" width="<?php print $options->width?>" height="<?php print $options->height?>"></div>
</div>