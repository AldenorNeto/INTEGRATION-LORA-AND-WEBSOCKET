String corpo PROGMEM (String appending, String txt, int duracao, String hora, String s, int indexClass){
return appending + String(R"=====(
<tr><td class='titulo'><input type='text' value=')=====")+txt+String(R"=====('></td>
<td><select class="duracao">
    <option value="1">5:00</option>
    <option value="2">10:00</option>
    <option value="3">15:00</option>
    <option value="4">20:00</option>
    <option value="5">25:00</option>
</select></td>
<td><input type="time" class="hora"></div></td>
<td><div class="DATA"><div class="semana">
    <label><input type="checkbox" class="S0"><div class="dom">D</div></label>
    <label><input type="checkbox" class="S1"><div class="seg">S</div></label>
    <label><input type="checkbox" class="S2"><div class="ter">T</div></label>
    <label><input type="checkbox" class="S3"><div class="qua">Q</div></label>
</div><div  class="semana">
    <label><input type="checkbox" class="S4"><div class="qui">Q</div></label>
    <label><input type="checkbox" class="S5"><div class="sex">S</div></label>
    <label><input type="checkbox" class="S6"><div class="sab">S</div></label>
</div></div></div></td>
<td><div class="umidade"><span class="umidad"></span>%</div></td>
<td><label class="estadoBomba"><input type="checkbox" class="bomba"><div></div></label></td></tr>
<script defer>
    document.querySelectorAll('.duracao')[)=====")+String(indexClass)+String(R"=====(].value = )=====")+String(duracao)+String(R"=====(
    document.querySelectorAll('.hora')[)=====")+String(indexClass)+String(R"=====(].value = ")=====")+hora+String(R"=====("
    for(let ind=0; ind < 7; ind++){
        document.querySelectorAll('.S'+ind)[)=====")+String(indexClass)+String(R"=====(].checked = parseInt(')=====")+s+R"=====('[ind])}</script>)====="; 
}
  